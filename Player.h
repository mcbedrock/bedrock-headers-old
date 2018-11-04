#pragma once

#include "entity/Mob.h"
#include "gamemode/GameType.h"

enum PlayerPermissions : char {
	VISITOR, MEMBER, OPERATOR, CUSTOM
};

struct Player : Mob {
	enum PositionMode {
		NORMAL, RESET, TELEPORT, PITCH
	};

	bool isCreative() const;

	unsigned char getClientSubId() const;

	NetworkIdentifier &getClientId() const;

	PlayerPermissions getPlayerPermissionLevel() const;

	bool isOperator() {
		return getPlayerPermissionLevel() == PlayerPermissions::OPERATOR;
	}

	virtual void setPlayerGameType(GameType);
};