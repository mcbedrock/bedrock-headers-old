#pragma once

#include "CommandRegistry.h"
#include "selector/CommandSelector.h"
#include "../extra/MinecraftHandle.h"

struct CommandMessage {
	struct MessageComponent {
		std::string text;
		std::unique_ptr<CommandSelector<Actor>> selector;

		MessageComponent(MessageComponent &&);
		MessageComponent(std::string const &);
		MessageComponent(std::unique_ptr<CommandSelector<Actor>> &&);

		MessageComponent &operator=(MessageComponent &&);

		~MessageComponent();
	};

	std::vector<MessageComponent> components;

	CommandMessage();

	static typeid_t<CommandRegistry> type_id() {
		static auto ret = type_id_minecraft_symbol<CommandRegistry>("_ZZ7type_idI15CommandRegistry14CommandMessageE8typeid_tIT_EvE2id");
		return ret;
	};

	std::string getMessage(CommandOrigin const &) const;

	~CommandMessage();
};