#pragma once

/**
 * @link https://github.com/pmmp/PocketMine-MP/blob/master/src/pocketmine/network/mcpe/protocol/types/WindowTypes.php
 */
enum struct ContainerType : char {
	INVENTORY = -1,
	CONTAINER = 0,
	WORKBENCH = 1,
	FURNACE = 2,
	ENCHANTMENT = 3,
	BREWING_STAND = 4,
	ANVIL = 5,
	DISPENSER = 6,
	DROPPER = 7,
	HOPPER = 8,
	CAULDRON = 9,
	MINECART_CHEST = 10,
	MINECART_HOPPER = 11,
	HORSE = 12,
	BEACON = 13,
	STRUCTURE_EDITOR = 14,
	TRADING = 15,
	COMMAND_BLOCK = 16,
	JUKEBOX = 17
};