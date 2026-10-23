#pragma once

#include "core/component.hpp"
#include "core/vec3.hpp"

struct CubeRenderer : Component
{
	Vec3 size = {32.0f, 32.0f, 32.0f};
	Vec3 color = {0.7f, 0.7f, 0.7f};
	bool visible = true;
};
