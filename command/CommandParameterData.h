#pragma once

#include <string>
#include <vector>
#include "CommandRegistry.h"
#include "../util/typeid.h"

enum CommandParameterDataType : int {
};

struct CommandParameterData {
	using ParseFn = bool (CommandRegistry::*)(void *, CommandRegistry::ParseToken const &, CommandOrigin const &, int,
	                                          std::string &, std::vector<std::string> &);
	typeid_t<CommandRegistry> tid;
	ParseFn parseFn;
	std::string name;
	char const *desc;
	int unk64;
	CommandParameterDataType type;
	int unk72;
	int offset;
	bool optional;

	CommandParameterData(typeid_t<CommandRegistry>,
	                     bool (CommandRegistry::*)(void *, CommandRegistry::ParseToken const &, CommandOrigin const &,
	                                               int, std::string &, std::vector<std::string> &) const, char const *,
	                     CommandParameterDataType, char const *, int, bool, int);

	CommandParameterData(CommandParameterData const &);

	CommandParameterData &operator=(CommandParameterData const &);
};