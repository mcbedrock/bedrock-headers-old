#pragma once

#include <bits/shared_ptr.h>
#include <memory>
#include <vector>
#include "../../entity/Actor.h"

template<typename T>
struct SelectorIterator {
	std::shared_ptr<std::vector<Actor *>> ref;
	typename std::vector<Actor *>::iterator it;

	SelectorIterator(std::shared_ptr<std::vector<Actor *>>, typename std::vector<Actor *>::iterator);

	SelectorIterator(SelectorIterator const &);

	SelectorIterator();

	SelectorIterator &operator=(SelectorIterator const &);

	bool operator==(SelectorIterator const &) const;

	bool operator!=(SelectorIterator const &) const;

	T &operator*();

	SelectorIterator operator++(int);

	SelectorIterator &operator++();

	~SelectorIterator();
};

template<typename T>
struct CommandSelectorResults {
	std::shared_ptr<std::vector<Actor *>> data;

	CommandSelectorResults(CommandSelectorResults const &);

	CommandSelectorResults(std::shared_ptr<std::vector<Actor *>>);

	SelectorIterator<T> begin() const;

	SelectorIterator<T> end() const;

	T *get() const;

	std::size_t size() const;

	bool empty() const;
};