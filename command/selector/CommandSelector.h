#pragma once

#include "CommandSelectorBase.h"
#include "CommandSelectorResults.h"

template<typename T>
struct CommandSelector : CommandSelectorBase {
	CommandSelector();

	CommandSelectorResults<T> results(CommandOrigin const &) const;
};