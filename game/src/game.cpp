#include "game/game.hpp"

#include <iostream>
#include <string>
#include <vector>

#include "engine/input.hpp"
#include "engine/map.hpp"
#include "game/combat.hpp"
#include "game/mob.hpp"
#include "game/player.hpp"

void run()
{
	const int tileLength = 32;
	char keyPressed;

	Player player(100, 50, 10, 0, {"♙", "player", {75, 50}});
	Mob mob1(100, 50, 8, 0, {"☠", "mob", {10 * 32, 20 * 32}});
	Mob mob2(100, 50, 8, 0, {"☠", "mob", {20 * 32, 7 * 32}});

	std::vector<GameObject *> objects = {
		&mob1.gameObject,
		&mob2.gameObject};
	std::vector<Mob *> mobs = {
		&mob1,
		&mob2};
	std::vector<std::string> tags = {"mob"};

	checkCombat(player, objects, mobs, tags, 1, tileLength);
	drawMap(player.gameObject, objects, tileLength);

	while (true)
	{
		keyPressed = readKey();

		switch (keyPressed)
		{
		case 'w':
			player.gameObject.position.line -= tileLength;
			break;
		case 's':
			player.gameObject.position.line += tileLength;
			break;
		case 'a':
			player.gameObject.position.column -= tileLength;
			break;
		case 'd':
			player.gameObject.position.column += tileLength;
			break;
		default:
			std::cout << "Invalid key pressed. Use 'w', 'a', 's', or 'd' to move the player." << std::endl;
			continue;
		}

		checkCombat(player, objects, mobs, tags, 1, tileLength);
		drawMap(player.gameObject, objects, tileLength);
	}
}
