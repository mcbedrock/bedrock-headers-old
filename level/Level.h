#pragma once

#include "../network/PacketSender.h"
#include "Dimension.h"
#include "../math/BlockPos.h"
#include "../entity/ActorRuntimeID.h"

struct ServerPlayer;
struct Actor;

class Level {
public:
	std::vector<std::unique_ptr<ServerPlayer>> &getUsers();

	std::vector<std::unique_ptr<ServerPlayer>> const &getUsers() const;

	BlockPos const &getDefaultSpawn() const;

	PacketSender *getPacketSender() const;

	//

	Actor *getMob(ActorUniqueID) const;

	ServerPlayer *getPlayer(ActorUniqueID) const;

	std::unique_ptr<Actor> takeEntity(ActorUniqueID);
};