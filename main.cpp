#include <iostream>
#include <vector>

#if defined(_WIN32)

#include <conio.h>

char readKey()
{
	return _getch();
}

#elif defined(__linux__)

#include <termio.h>
#include <unistd.h>

char readKey()
{
	termios oldSettings{};
	termios newSettings{};

	tcgetattr(STDIN_FILENO, &oldSettings);

	newSettings = oldSettings;
	newSettings.c_lflag &= ~(ICANON | ECHO);

	tcsetattr(STDIN_FILENO, TCSANOW, &newSettings);

	char key;
	read(STDIN_FILENO, &key, 1);

	tcsetattr(STDIN_FILENO, TCSANOW, &oldSettings);

	return key;
}

#else

#error "Sistema operacional não suportado"

#endif

struct Vec2
{
	int column;
	int line;
};

struct Player
{
	int life;
	int mana;
	char img;

	Vec2 position;
};

void drawMap(const Player &player, int tileLength)
{
	for (int i = 0; i < tileLength; ++i)
	{
		for (int j = 0; j < tileLength; ++j)
		{
			if (j == 0 || j == tileLength - 1 || i == 0 || i == tileLength - 1)
			{
				std::cout << "#";
			}
			else if (i == player.position.line / tileLength && j == player.position.column / tileLength)
			{
				std::cout << player.img;
			}
			else
			{
				std::cout << "*";
			}
		}

		std::cout << "\n";
	}
}

int main()
{
	int tileLength = 32;
	char keyPressed;

	Player player = {
		.life = 100,
		.mana = 50,
		.img = 'P',
		.position = {
			.column = 75,
			.line = 50}};

	Vec2 positionOnMap = {
		player.position.column / tileLength,
		player.position.line / tileLength};

	drawMap(player, tileLength);

	while (true)
	{
		keyPressed = readKey();

		switch (keyPressed)
		{
		case 'w':
			player.position.line -= tileLength;
			drawMap(player, tileLength);
			break;
		case 's':
			player.position.line += tileLength;
			drawMap(player, tileLength);
			break;
		case 'a':
			player.position.column -= tileLength;
			drawMap(player, tileLength);
			break;
		case 'd':
			player.position.column += tileLength;
			drawMap(player, tileLength);
			break;
		default:
			std::cout << "Invalid key pressed. Use 'w', 'a', 's', or 'd' to move the player." << std::endl;
			break;
		}
	};
}