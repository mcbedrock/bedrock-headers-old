#pragma once

#include "CommandVersion.h"
#include <memory>
#include <vector>
#include "../math/Vec3.h"
#include "../math/BlockPos.h"
#include "../network/ServerPlayer.h"
#include "../level/Level.h"
#include "../mce/UUID.h"

class Command;

class CommandParameterData;

enum struct OriginType : char {
	PLAYER = 0,
	BLOCK = 1,
	MINECART_BLOCK = 2,
	DEV_CONSOLE = 3,
	TEST = 4,
	AUTOMATION_PLAYER = 5,
	CLIENT_AUTOMATION = 6,
	DEDICATED_SERVER = 7,
	ENTITY = 8,
	VIRTUAL = 9,
	GAME_ARGUMENT = 10,
	ENTITY_SERVER = 11
};
enum CommandPermissionLevel : unsigned char {
	NORMAL = 0,
	GAMEMASTER = 1, //operator
	HOST = 2,
	AUTOMATION = 3,
	ADMIN = 4
};
enum CommandFlag : char {};
struct CommandOriginData {};

struct CommandOrigin {
	mce::UUID uuid;

	CommandOrigin();

	virtual ~CommandOrigin();

	virtual std::string getRequestId() const;

	virtual std::string getName() const;

	virtual BlockPos getBlockPosition() const;

	virtual Vec3 getWorldPosition() const;

	virtual Level *getLevel() const;

	virtual Dimension *getDimension() const;

	virtual Actor *getEntity() const;

	virtual CommandPermissionLevel getPermissionLevel() const;

	virtual std::unique_ptr<CommandOrigin> clone() const;

	virtual bool canCallHiddenCommands() const;

	virtual bool hasChatPerms() const;

	virtual bool hasTellPerms() const;

	virtual bool canUseAbility(std::string const &) const;

	virtual NetworkIdentifier getSourceId() const;

	virtual char getSourceSubId() const;

	virtual CommandOrigin *getOutputReceiver() const;

	virtual OriginType getOriginType() const;

	virtual CommandOriginData toCommandOriginData() const;

	virtual mce::UUID const &getUUID() const;

	virtual void setUUID(mce::UUID const &);
};

class CommandRegistry {

public:
	struct ParseToken {
		std::string toString() const;
	};

	struct Overload {
		CommandVersion version;

		std::unique_ptr<Command> (*allocator)();

		std::vector<CommandParameterData> params;
		int filler;

		Overload(CommandVersion version, std::unique_ptr<Command> (*allocator)()) : version(version),
																					allocator(allocator) {}
	};

	struct Signature {
		char filler[64];
		std::vector<CommandRegistry::Overload> overloads;
	};

	Signature *findCommand(std::string const &);

	void buildOverload(Overload &);

	void registerOverloadInternal(Signature &, Overload &);

	void registerCommand(std::string const &, char const *, CommandPermissionLevel, CommandFlag, CommandFlag);

	template<typename T>
	bool parse(void *, ParseToken const &, CommandOrigin const &, int, std::string &, std::vector<std::string> &) const;

	template<typename T>
	static std::unique_ptr<Command> allocateCommand() { return std::unique_ptr<Command>(new T()); }

	template<typename T, typename... Args>
	void registerOverload(const char *name, CommandVersion version, Args &&... args) {
		Signature *signature = findCommand(name);
		signature->overloads.emplace_back(version, allocateCommand<T>);
		Overload &overload = *signature->overloads.rbegin();
		buildOverload(overload);
		overload.params = {args...};
		registerOverloadInternal(*signature, overload);
	}

	template<typename F>
	void
	registerCustomOverload(const char *name, CommandVersion version, std::unique_ptr<Command> (*allocator)(), F f) {
		Signature *signature = findCommand(name);
		signature->overloads.emplace_back(version, allocator);
		Overload &overload = *signature->overloads.rbegin();
		buildOverload(overload);
		f(overload);
		registerOverloadInternal(*signature, overload);
	}

	void addSoftEnum(std::string const &, std::vector<std::string>);

	int addEnumValues(std::string const &name, std::vector<std::string> const &data);
};