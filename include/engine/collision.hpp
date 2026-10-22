#pragma once

#include <string>
#include <vector>

#include "engine/gameobject.hpp"

std::vector<GameObject *> detectObjectsInRadius(
	GameObject &center,
	std::vector<GameObject *> &objects,
	std::vector<std::string> &tags,
	int radius,
	int tileLength);
