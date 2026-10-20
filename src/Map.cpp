#include "Map.hpp"

#include <iostream>

void drawMap(
	const Player &player,
	const std::vector<GameObject> &objects,
	int tileLength)
{
	for (int i = 0; i < tileLength; ++i)
	{
		for (int j = 0; j < tileLength; ++j)
		{
			if (j == 0 || j == tileLength - 1 || i == 0 || i == tileLength - 1)
			{
				std::cout << "#";
			}
			else if (i == player.gameObject.position.line / tileLength &&
					 j == player.gameObject.position.column / tileLength)
			{
				std::cout << player.gameObject.img;
			}
			else
			{
				bool objectFound = false;

				for (const GameObject &object : objects)
				{
					if (i == object.position.line / tileLength && j == object.position.column / tileLength)
					{
						std::cout << object.img;
						objectFound = true;
						break;
					}
				}

				if (!objectFound)
				{
					std::cout << "*";
				}
			}
		}

		std::cout << "\n";
	}
}
