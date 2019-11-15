#include <SFML/Graphics.hpp>
#include "Menu.h"

//#include "Game.h"

int main()
{
	Menu *menu = new Menu();
	menu->Start();
	delete(menu);
	return 0;
}
