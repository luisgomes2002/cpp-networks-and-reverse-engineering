#include "game/combat.hpp"

#include <iostream>

#include "engine/collision.hpp"

void checkCombat(
	Player &player,
	std::vector<GameObject *> &objects,
	std::vector<Mob *> &mobs,
	std::vector<std::string> &tags,
	int radius,
	int tileLength)
{
	std::vector<GameObject *> nearbyObjects = detectObjectsInRadius(
		player.gameObject,
		objects,
		tags,
		radius,
		tileLength);

	for (GameObject *object : nearbyObjects)
	{
		for (Mob *mob : mobs)
		{
			if (&mob->gameObject == object)
			{
				combat(player, *mob);
				return;
			}
		}
	}
}

int attack(Character &player, Character &mob)
{
	std::cout << "Você atacou o inimigo!" << std::endl;
	return 0;
}

void combat(Player &player, Mob &mob)
{
	std::cout << "Combat initiated!" << std::endl;
	std::cout << "Press 'a' to attack or 'r' to run away." << std::endl;
	char c = std::cin.get();

	if (c == 'a')
	{
		std::cout << "Você entrou em combate" << std::endl;

		std::cout << "Pressione 'a' para atacar      Pressione 'r' para fugir." << std::endl;
		std::cout << "Pressione 'h' para curar       Pressione 'b' para usar um buffer." << std::endl;

		char action = std::cin.get();

		if (action == 'a')
		{
			attack(player, mob);
		}
	}
}
