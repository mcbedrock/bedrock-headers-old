#pragma once

#include "Command.h"
#include "../level/Level.h"
//#include "../entity/Actor.h"
struct Actor;

class TeleportCommand : public Command {
public:
	~TeleportCommand() = default;

	void teleport(Actor &, Vec3, Vec3 *, DimensionId) const;
};