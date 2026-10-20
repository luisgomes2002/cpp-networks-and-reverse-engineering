#include "Input.hpp"

#if defined(_WIN32)

#include <conio.h>

char readKey()
{
	return _getch();
}

#elif defined(__linux__)

#include <termios.h>
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
