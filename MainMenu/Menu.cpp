#include "Menu.h"

Menu::Menu()
{
	smash_It_image.loadFromFile("images/Smash_It_Game.png");
	time_climb_image.loadFromFile("images/Time_climb_Game.png");
	labyrinth_image.loadFromFile("images/Labyrinth_Game.png");
	aerohockey_image.loadFromFile("images/aerohockey_Game.png");
	territory_image.loadFromFile("images/Territory_Game.png");

	initialized = false;
}

Menu::~Menu()
{
	std::for_each(_menuItems.begin(), _menuItems.end(), menuItemsDeallocator());
}


Menu::MenuItem::MenuItem(sf::Vector2f position, buttonAction action, std::string fileName)
	:_position(position), text("", font, 120), _action(action), _rect(_position.x,_position.y, 0,0)
{
	//font.loadFromFile("font/18123.ttf");
	_image.loadFromFile(fileName);
	_image.createMaskFromColor(sf::Color(255, 255, 255));
	_texture.loadFromImage(_image);
	_sprite.setTexture(_texture);
	_sprite.setPosition(_position);
	animationFrame = 0;
	_rect.width = _sprite.getTexture()->getSize().x;
	_rect.height = _sprite.getTexture()->getSize().y;

	_center = sf::Vector2f(position.x + _sprite.getTexture()->getSize().x / 2, position.y + _sprite.getTexture()->getSize().y / 2);
}

void Menu::Start(void)
{
	_mainWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Menu");


	_menuState = Menu::GAME_SELECTION;	
	_currentGame = 0;

	while (!IsExiting())
	{
		MenuLoop();
	}

	Menu::_mainWindow.close();
}


void Menu::Init_GAME_SELECTION()
{



	if (initialized) {
		return;
	}
	else
	{
		background_image.loadFromFile("images/back_ground_1.png");
		background_texture.loadFromImage(background_image);
		background_sprite.setTexture(background_texture);

		MenuItem *play_Button = new MenuItem(sf::Vector2f(500, 600), PLAY, "images/PLAY_button.png");
		MenuItem *next_Button = new MenuItem(sf::Vector2f(1050, 650), NEXT, "images/NEXT_button.png");
		MenuItem *previous_Button = new MenuItem(sf::Vector2f(150, 650), PREVIOUS, "images/PREV_button.png");
		MenuItem *mainGame = new MenuItem(sf::Vector2f(350, 100), NOTHING, "images/Smash_It_Game.png");
		MenuItem *leftGame = new MenuItem(sf::Vector2f(50, 200), NOTHING, "images/notMainGame.png");
		MenuItem *rightGame = new MenuItem(sf::Vector2f(1150, 200), NOTHING, "images/notMainGame.png");

		_menuItems.insert(std::pair<std::string, MenuItem*>("play_Button", play_Button));
		_menuItems.insert(std::pair<std::string, MenuItem*>("next_Button", next_Button));
		_menuItems.insert(std::pair<std::string, MenuItem*>("previous_Button", previous_Button));
		_menuItems.insert(std::pair<std::string, MenuItem*>("mainGame", mainGame));
		_menuItems.insert(std::pair<std::string, MenuItem*>("leftGame", leftGame));
		_menuItems.insert(std::pair<std::string, MenuItem*>("rightGame", rightGame));

		initialized = true;
		std::cout << "GAME_SELCTION initialized";
	}
	
}

void Menu::Init_PLAYING()
{
	if (initialized) {
		return;
	}
	else
	{
		_menuItems.erase(_menuItems.begin(), _menuItems.end());

		background_image.loadFromFile("images/back_ground_1.png");
		background_texture.loadFromImage(background_image);
		background_sprite.setTexture(background_texture);

		MenuItem *play_Button = new MenuItem(sf::Vector2f(500, 600), PLAY, "images/PLAY_button.png");
		MenuItem *next_Button = new MenuItem(sf::Vector2f(1050, 650), NEXT, "images/NEXT_button.png");
	

		_menuItems.insert(std::pair<std::string, MenuItem*>("play_Button", play_Button));
		_menuItems.insert(std::pair<std::string, MenuItem*>("next_Button", next_Button));


		initialized = true;
		std::cout << "PLAY initialized";
	}

}



void Menu::MenuLoop()
{
	//not anderstanded for what
	/*sf::Event currentEvent;
	_mainWindow.pollEvent(currentEvent);*/


	switch (_menuState)
	{
		case Menu::GAME_SELECTION:
		{
			game_selection_Menu();
			break;
		}
		case Menu::PLAYING:
		{
			playing();
			break;
		}
		case Menu::SCORE_BOARD:
		{
			score_board();
			break;
		}
	}
	
	_mainWindow.display();
	
}




void Menu::playing()
{
	Init_PLAYING();
	game_selection_Menu_Draw();
	playing_Update();
}

void Menu::game_selection_Menu()
{
	Init_GAME_SELECTION();
	game_selection_Menu_Draw();
	game_selection_Menu_Update();

}

void Menu::score_board()
{

}


void Menu::game_selection_Menu_Draw()
{
	_mainWindow.clear(sf::Color(0, 0, 0));
	_mainWindow.draw(background_sprite);
	std::map<std::string, MenuItem*>::iterator it;

	for (it = _menuItems.begin(); it != _menuItems.end(); it++)
	{
		_mainWindow.draw((*it).second->_sprite);
	}	
	
}

void Menu::game_selection_Menu_Update()
{
	buttonAction clicResult = GetMenuResponse(_mainWindow);
	switch (clicResult)
	{
	case Menu::NOTHING:
		break;
	case Menu::PLAY:
		_menuState = PLAYING;
		initialized = false;
		break;
	case Menu::NEXT:
		_currentGame++;
		if (_currentGame > 4) _currentGame = 0;
		break;
	case Menu::PREVIOUS:
		_currentGame--;
		if (_currentGame < 0) _currentGame = 4;
		break;
	case Menu::EXIT:
		_menuState = EXITING;
		break;
	default:
		break;
	}

	switch (_currentGame)
	{
	case Menu::SMASH_IT:
		Get("mainGame")->_texture.loadFromImage(smash_It_image);

		Get("leftGame")->_texture.loadFromImage(territory_image);
		Get("leftGame")->_sprite.setTextureRect(Get("mainGame")->_sprite.getTextureRect());
		Get("leftGame")->_sprite.setScale(0.3, 0.7);

		Get("rightGame")->_texture.loadFromImage(time_climb_image);
		Get("rightGame")->_sprite.setTextureRect(Get("mainGame")->_sprite.getTextureRect());
		Get("rightGame")->_sprite.setScale(0.3, 0.7);
		break;
	case Menu::TIME_CLIMB:
		Get("mainGame")->_texture.loadFromImage(time_climb_image);

		Get("leftGame")->_texture.loadFromImage(smash_It_image);
		Get("leftGame")->_sprite.setTextureRect(Get("mainGame")->_sprite.getTextureRect());
		Get("leftGame")->_sprite.setScale(0.3, 0.7);

		Get("rightGame")->_texture.loadFromImage(labyrinth_image);
		Get("rightGame")->_sprite.setTextureRect(Get("mainGame")->_sprite.getTextureRect());
		Get("rightGame")->_sprite.setScale(0.3, 0.7);
		break;
	case Menu::LABYRINTH:
		Get("mainGame")->_texture.loadFromImage(labyrinth_image);

		Get("leftGame")->_texture.loadFromImage(time_climb_image);
		Get("leftGame")->_sprite.setTextureRect(Get("mainGame")->_sprite.getTextureRect());
		Get("leftGame")->_sprite.setScale(0.3, 0.7);

		Get("rightGame")->_texture.loadFromImage(aerohockey_image);
		Get("rightGame")->_sprite.setTextureRect(Get("mainGame")->_sprite.getTextureRect());
		Get("rightGame")->_sprite.setScale(0.3, 0.7);
		break;
	case Menu::AEROHOCKEY:
		Get("mainGame")->_texture.loadFromImage(aerohockey_image);

		Get("leftGame")->_texture.loadFromImage(labyrinth_image);
		Get("leftGame")->_sprite.setTextureRect(Get("mainGame")->_sprite.getTextureRect());
		Get("leftGame")->_sprite.setScale(0.3, 0.7);

		Get("rightGame")->_texture.loadFromImage(territory_image);
		Get("rightGame")->_sprite.setTextureRect(Get("mainGame")->_sprite.getTextureRect());
		Get("rightGame")->_sprite.setScale(0.3, 0.7);
		break;
	case Menu::TERRITORY:
		Get("mainGame")->_texture.loadFromImage(territory_image);

		Get("leftGame")->_texture.loadFromImage(aerohockey_image);
		Get("leftGame")->_sprite.setTextureRect(Get("mainGame")->_sprite.getTextureRect());
		Get("leftGame")->_sprite.setScale(0.3, 0.7);

		Get("rightGame")->_texture.loadFromImage(smash_It_image);
		Get("rightGame")->_sprite.setTextureRect(Get("mainGame")->_sprite.getTextureRect());
		Get("rightGame")->_sprite.setScale(0.3, 0.7);
		break;
	default:
		break;
	}
}


void Menu::playing_Draw()
{
	_mainWindow.clear(sf::Color(0, 0, 0));
	_mainWindow.draw(background_sprite);

}

void Menu::playing_Update()
{

}

bool Menu::IsExiting()//для остановки GameLoop()
{
	if (_menuState == Menu::EXITING)
		return true;
	else
		return false;
}

sf::RenderWindow& Menu::GetWindow()
{
	return Menu::_mainWindow;
}

Menu::buttonAction Menu::HandleClick(sf::RenderWindow& window, int x, int y)				//Проверка куда кликнули мышью
{
	std::map<std::string, MenuItem*>::iterator it;

	for (it = _menuItems.begin(); it != _menuItems.end(); it++)
	{
		if ((*it).second->_rect.contains(x,y))
		{
			return (*it).second->_action;										//Возврацает номер "сцены" (состояния)
		}
	}

	return NOTHING;
}

Menu::buttonAction Menu::GetMenuResponse(sf::RenderWindow& window)
{
	sf::Event menuEvent;

		while (window.pollEvent(menuEvent))
		{
			if (menuEvent.type == sf::Event::MouseButtonPressed)
			{
				return HandleClick(window, menuEvent.mouseButton.x, menuEvent.mouseButton.y);
			}
			if (menuEvent.type == sf::Event::Closed)
			{
				return EXIT;
			}
		}
}


void Menu::MenuItem::Move(sf::Vector2f pos)
{
	
}

Menu::MenuItem* Menu::Get(std::string name) const
{
	std::map<std::string, Menu::MenuItem*>::const_iterator results = _menuItems.find(name);
	if (results == _menuItems.end())
		return NULL;
	return results->second;
}


float Menu::dist2(sf::Vector2f const & p1, sf::Vector2f const & p2)
{
	return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

//Menu::menuState Menu::_menuState = Menu::GAME_SELECTION;
//sf::RenderWindow Menu::_mainWindow;
//sf::Image Menu::background_image;
//sf::Texture Menu::background_texture;
//sf::Sprite Menu::background_sprite;
//std::map<std::string, Menu::MenuItem*> Menu::_menuItems;