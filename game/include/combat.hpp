#pragma once

#include <string>
#include <vector>

#include "game/character.hpp"
#include "game/mob.hpp"
#include "game/player.hpp"

int attack(Character &player, Character &mob);
void combat(Player &player, Mob &mob);
void checkCombat(
	Player &player,
	std::vector<GameObject *> &objects,
	std::vector<Mob *> &mobs,
	std::vector<std::string> &tags,
	int radius,
	int tileLength);
