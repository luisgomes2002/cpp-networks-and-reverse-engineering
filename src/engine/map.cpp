#include "engine/map.hpp"

#include <iostream>
#include <string>

void drawMap(
	const GameObject &player,
	const std::vector<GameObject *> &objects,
	int tileLength)
{
	const std::string wall = "█";
	const std::string ground = "·";

	for (int i = 0; i < tileLength; ++i)
	{
		for (int j = 0; j < tileLength; ++j)
		{
			if (j == 0 || j == tileLength - 1 || i == 0 || i == tileLength - 1)
			{
				std::cout << wall;
			}
			else if (i == player.position.line / tileLength &&
					 j == player.position.column / tileLength)
			{
				std::cout << player.img;
			}
			else
			{
				bool objectFound = false;

				for (const GameObject *object : objects)
				{
					if (i == object->position.line / tileLength && j == object->position.column / tileLength)
					{
						std::cout << object->img;
						objectFound = true;
						break;
					}
				}

				if (!objectFound)
				{
					std::cout << ground;
				}
			}
		}

		std::cout << "\n";
	}

	std::cout << "\n";
}
