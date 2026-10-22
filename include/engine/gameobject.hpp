#pragma once

#include <string>

#include "engine/vec2.hpp"

struct GameObject
{
	std::string img;
	std::string tag = "object";
	Vec2 position;
};
