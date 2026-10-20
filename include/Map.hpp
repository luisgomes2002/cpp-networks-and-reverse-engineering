#pragma once
#include <vector>

#include "Player.hpp"

void drawMap(
	const Player &player,
	const std::vector<GameObject> &objects,
	int tileLength);
