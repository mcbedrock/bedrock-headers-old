#pragma once

template<typename Type, typename Store>
struct AutomaticID {
	Store v;
	AutomaticID();
	AutomaticID(Store v) : v(v) {}
	Store value() const;
	bool operator!=(AutomaticID const &) const;
	bool operator==(AutomaticID const &) const;
	operator Store() const { return v; }
	static Store _makeRuntimeID();
};

struct Dimension;

enum VanillaDimensions : int {
	Overworld = 0,
	Nether = 1,
	TheEnd = 2,
	Undefined = 3
};

using DimensionId = AutomaticID<Dimension, int>;

struct Dimension {
	DimensionId &getId() const;
};