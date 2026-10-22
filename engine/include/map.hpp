#pragma once

#include <vector>

#include "gameobject.hpp"

void drawMap(
	const GameObject &player,
	const std::vector<GameObject *> &objects,
	int tileLength);
