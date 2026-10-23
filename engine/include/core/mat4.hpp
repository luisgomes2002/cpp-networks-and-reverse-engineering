#pragma once

#include "core/vec3.hpp"

struct Mat4
{
	float values[16] = {};
};

Mat4 multiply(const Mat4 &left, const Mat4 &right);
Mat4 perspective(float fieldOfViewDegrees, float aspect, float nearPlane, float farPlane);
Mat4 orthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane);
Mat4 translation(const Vec3 &position);
Mat4 rotationX(float degrees);
Mat4 scale(const Vec3 &size);
