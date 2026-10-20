#include <iostream>

#include "Input.hpp"
#include "Map.hpp"

int main()
{
	int tileLength = 32;
	char keyPressed;

	Player player = {
		.life = 100,
		.mana = 50,
		.gameObject = {.img = 'P',
					   .position = {
						   .column = 75,
						   .line = 50}}};

	Player mob1 = {
		.life = 100,
		.mana = 50,
		.gameObject = {.img = 'M',
					   .position = {
						   .column = 32,
						   .line = 32}}};

	Player mob2 = {
		.life = 100,
		.mana = 50,
		.gameObject = {.img = 'M',
					   .position = {
						   .column = 64,
						   .line = 64}}};

	std::vector<GameObject> objects = {
		mob1.gameObject,
		mob2.gameObject};

	drawMap(player, objects, tileLength);

	while (true)
	{
		keyPressed = readKey();

		switch (keyPressed)
		{
		case 'w':
			player.gameObject.position.line -= tileLength;
			drawMap(player, objects, tileLength);
			break;
		case 's':
			player.gameObject.position.line += tileLength;
			drawMap(player, objects, tileLength);
			break;
		case 'a':
			player.gameObject.position.column -= tileLength;
			drawMap(player, objects, tileLength);
			break;
		case 'd':
			player.gameObject.position.column += tileLength;
			drawMap(player, objects, tileLength);
			break;
		default:
			std::cout << "Invalid key pressed. Use 'w', 'a', 's', or 'd' to move the player." << std::endl;
			break;
		}
	}
}
