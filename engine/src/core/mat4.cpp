#include "core/mat4.hpp"

#include <cmath>

Mat4 multiply(const Mat4 &left, const Mat4 &right)
{
	Mat4 result;

	for (int column = 0; column < 4; ++column)
	{
		for (int row = 0; row < 4; ++row)
		{
			for (int index = 0; index < 4; ++index)
			{
				result.values[column * 4 + row] +=
					left.values[index * 4 + row] *
					right.values[column * 4 + index];
			}
		}
	}

	return result;
}

Mat4 perspective(float fieldOfViewDegrees, float aspect, float nearPlane, float farPlane)
{
	const float radians = fieldOfViewDegrees * 3.14159265f / 180.0f;
	const float tangent = std::tan(radians / 2.0f);

	Mat4 result;
	result.values[0] = 1.0f / (aspect * tangent);
	result.values[5] = 1.0f / tangent;
	result.values[10] = -(farPlane + nearPlane) / (farPlane - nearPlane);
	result.values[11] = -1.0f;
	result.values[14] = -(2.0f * farPlane * nearPlane) / (farPlane - nearPlane);
	return result;
}

Mat4 orthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane)
{
	Mat4 result;
	result.values[0] = 2.0f / (right - left);
	result.values[5] = 2.0f / (top - bottom);
	result.values[10] = -2.0f / (farPlane - nearPlane);
	result.values[12] = -(right + left) / (right - left);
	result.values[13] = -(top + bottom) / (top - bottom);
	result.values[14] = -(farPlane + nearPlane) / (farPlane - nearPlane);
	result.values[15] = 1.0f;
	return result;
}

Mat4 translation(const Vec3 &position)
{
	Mat4 result;
	result.values[0] = 1.0f;
	result.values[5] = 1.0f;
	result.values[10] = 1.0f;
	result.values[12] = position.x;
	result.values[13] = position.y;
	result.values[14] = position.z;
	result.values[15] = 1.0f;
	return result;
}

Mat4 rotationX(float degrees)
{
	const float radians = degrees * 3.14159265f / 180.0f;
	const float cosine = std::cos(radians);
	const float sine = std::sin(radians);

	Mat4 result;
	result.values[0] = 1.0f;
	result.values[5] = cosine;
	result.values[6] = sine;
	result.values[9] = -sine;
	result.values[10] = cosine;
	result.values[15] = 1.0f;
	return result;
}

Mat4 scale(const Vec3 &size)
{
	Mat4 result;
	result.values[0] = size.x;
	result.values[5] = size.y;
	result.values[10] = size.z;
	result.values[15] = 1.0f;
	return result;
}
