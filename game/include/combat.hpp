#pragma once

#include <string>
#include <vector>

#include "character.hpp"
#include "mob.hpp"
#include "player.hpp"

int attack(Character &player, Character &mob);
void combat(Player &player, Mob &mob);
void checkCombat(
	Player &player,
	std::vector<GameObject *> &objects,
	std::vector<Mob *> &mobs,
	std::vector<std::string> &tags,
	int radius,
	int tileLength);
