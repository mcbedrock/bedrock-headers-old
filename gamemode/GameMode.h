#pragma once

#include "../math/BlockPos.h"

struct ServerPlayer;

struct GameMode {
	void *vt;
	ServerPlayer *player;
};