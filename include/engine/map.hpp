#pragma once

#include <vector>

#include "engine/gameobject.hpp"

void drawMap(
	const GameObject &player,
	const std::vector<GameObject *> &objects,
	int tileLength);
