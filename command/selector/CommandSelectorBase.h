#pragma once

#include "../Command.h"

enum struct CommandSelectionType;
enum struct CommandSelectionOrder;

template<typename T>
struct InvertableFilter {
	T value;       // 0
	bool inverted; // sizeof(T)

	InvertableFilter(InvertableFilter const &);

	InvertableFilter(InvertableFilter &&);

	~InvertableFilter();
};

struct CommandSelectorBase {
	int version;
	CommandSelectionType type;
	CommandSelectionOrder order;
	std::vector<InvertableFilter<std::string>> nameFilter;
	std::vector<InvertableFilter<ActorType>> typeFilter;
	std::vector<std::function<bool(CommandOrigin const &, Actor &)>> filters;
	BlockPos source_pos;
	float radius_min;
	float radius_max;
	std::size_t result_count;
	bool include_dead_players;
	bool use_radius1;
	bool use_radius2;
	bool b139;
	bool player_only;

	CommandSelectorBase(bool);

	CommandSelectionType getType() const;

	CommandSelectionOrder getOrder() const;

	std::string getExplicitPlayerName() const;

	std::string getName() const;

	void addNameFilter(InvertableFilter<std::string> const &);

	void addTypeFilter(InvertableFilter<std::string> const &);

	void addFilter(std::function<bool(CommandOrigin const &, Actor &)>);

	bool compile(CommandOrigin const &, std::string &);

	bool filter(CommandOrigin const &, Actor &, float);

	bool hasName() const;

	bool isExpansionAllowed(CommandOrigin const &) const;

	bool matchName(Actor &) const;

	bool matchType(Actor &) const;

	std::shared_ptr<std::vector<Actor *>> newResults() const;

	void setBox(BlockPos);

	void setIncludeDeadPlayers(bool);

	void setOrder(CommandSelectionOrder);

	//void setPosition(CommandPosition);

	void setType(CommandSelectionOrder);

	void setVersion(int);

	virtual ~CommandSelectorBase() = default;
};