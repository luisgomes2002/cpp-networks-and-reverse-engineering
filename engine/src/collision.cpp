#include "engine/collision.hpp"

#include <algorithm>
#include <cstdlib>

std::vector<GameObject *> detectObjectsInRadius(
	GameObject &center,
	std::vector<GameObject *> &objects,
	std::vector<std::string> &tags,
	int radius,
	int tileLength)
{
	std::vector<GameObject *> nearbyObjects;

	int centerColumn = center.position.column / tileLength;
	int centerLine = center.position.line / tileLength;

	for (GameObject *object : objects)
	{
		bool hasValidTag = std::find(tags.begin(), tags.end(), object->tag) != tags.end();

		if (!hasValidTag)
		{
			continue;
		}

		int objectColumn = object->position.column / tileLength;
		int objectLine = object->position.line / tileLength;

		int columnDifference = std::abs(objectColumn - centerColumn);
		int lineDifference = std::abs(objectLine - centerLine);

		if (columnDifference <= radius && lineDifference <= radius &&
			(columnDifference != 0 || lineDifference != 0))
		{
			nearbyObjects.push_back(object);
		}
	}

	return nearbyObjects;
}
