#pragma once

#include <string>
#include "../level/Level.h"
#include "../math/BlockPos.h"

struct Actor;

struct TeleportCommand {
	void teleport(Actor &, Vec3, Vec3 *, DimensionId) const;
};

enum ActorType : uint {};

struct HitResult {
	Vec3 const &getPos() const;
};

struct ProjectileComponent {
	Actor &getEntity();
};

struct Actor {
	const std::string &getNameTag() const;

	const char *getName() { return getNameTag().c_str(); }

	Level &getLevel();

	Dimension &getDimension() const;

	DimensionId getDimensionId() const;

	VanillaDimensions getDimensionType() {
		return (VanillaDimensions) getDimension().getId().value();
	}

	Vec3 calcCenterPos() const;

	BlockPos asBlockPos() const {
		return BlockPos(calcCenterPos());
	}

	void teleport(Vec3 const &v3, VanillaDimensions dimension = VanillaDimensions::Undefined) {
		((TeleportCommand *) nullptr)->teleport(
			*this,
			v3,
			new Vec3(calcCenterPos()),
			dimension == VanillaDimensions::Undefined ? getDimensionId() : DimensionId(dimension)
		);
	}

	void teleportToSpawn() {
		teleport(Vec3(getLevel().getDefaultSpawn()), VanillaDimensions::Overworld);
	}

	virtual ~Actor();
};