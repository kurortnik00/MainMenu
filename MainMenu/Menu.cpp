#include "Menu.h"

Menu::Menu()
{
	smash_It_image.loadFromFile("images/Smash_It_Game.png");
	time_climb_image.loadFromFile("images/Time_climb_Game.png");
	labyrinth_image.loadFromFile("images/Labyrinth_Game.png");
	aerohockey_image.loadFromFile("images/aerohockey_Game.png");
	territory_image.loadFromFile("images/Territory_Game.png");

	level_1.loadFromFile("images/level_1_m.png");
	level_2.loadFromFile("images/level_2_m.png");
	level_3.loadFromFile("images/level_3_m.png");
	level_4.loadFromFile("images/level_4_m.png");
	level_5.loadFromFile("images/level_5_m.png");

	background_image.loadFromFile("images/back_ground_1.png");
	background_texture.loadFromImage(background_image);
	background_sprite.setTexture(background_texture);

	
	_font.loadFromFile("font/18123.ttf");

	initialized = false;
}

Menu::~Menu()
{
	std::for_each(_menuItems.begin(), _menuItems.end(), menuItemsDeallocator());
}


Menu::MenuItem::MenuItem(sf::Vector2f position, buttonAction action, std::string fileName, bool maskFromCollor = false)
	:_position(position), _action(action), _rect(_position.x,_position.y, 0,0)
{
	_image.loadFromFile(fileName);
	if (maskFromCollor) _image.createMaskFromColor(sf::Color(255, 255, 255));
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
	_currentLabyrinthLevel = 0;

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
		std::for_each(_menuItems.begin(), _menuItems.end(), menuItemsDeallocator());
		_menuItems.erase(_menuItems.begin(), _menuItems.end());
		

		

		MenuItem *play_Button = new MenuItem(sf::Vector2f(500, 600), PLAY, "images/PLAY_button.png", true);
		MenuItem *next_Button = new MenuItem(sf::Vector2f(1050, 650), NEXT, "images/NEXT_button.png", true);
		MenuItem *previous_Button = new MenuItem(sf::Vector2f(150, 650), PREVIOUS, "images/PREV_button.png", true);
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
		std::for_each(_menuItems.begin(), _menuItems.end(), menuItemsDeallocator());
		_menuItems.erase(_menuItems.begin(), _menuItems.end());
		switch (_currentGame)
		{
		case Menu::SMASH_IT:
		{
			MenuItem *back_Button = new MenuItem(sf::Vector2f(SCREEN_WIDTH / 2 - 200, 300), BACK, "images/back_button.png");
			MenuItem *topScore_Button = new MenuItem(sf::Vector2f(SCREEN_WIDTH / 2 - 200, 450), TOPSCORE, "images/top_score_button.png");

			_menuItems.insert(std::pair<std::string, MenuItem*>("back_Button", back_Button));
			_menuItems.insert(std::pair<std::string, MenuItem*>("topScore_Button", topScore_Button));
			break;
		}

		case Menu::TIME_CLIMB:
		{
			MenuItem *set_pos_Button = new MenuItem(sf::Vector2f(SCREEN_WIDTH / 2 - 200, 150), SETPOS, "images/set_pos_button.png");
			MenuItem *back_Button = new MenuItem(sf::Vector2f(SCREEN_WIDTH / 2 - 200, 300), BACK, "images/back_button.png");
			MenuItem *topScore_Button = new MenuItem(sf::Vector2f(SCREEN_WIDTH / 2 - 200, 450), TOPSCORE, "images/top_score_button.png");

			_menuItems.insert(std::pair<std::string, MenuItem*>("set_pos_Button", set_pos_Button));
			_menuItems.insert(std::pair<std::string, MenuItem*>("back_Button", back_Button));
			_menuItems.insert(std::pair<std::string, MenuItem*>("topScore_Button", topScore_Button));
			break;
		}
		case Menu::LABYRINTH:
		{
			MenuItem *back_Button = new MenuItem(sf::Vector2f(20, 20), BACK, "images/back_button.png");
			back_Button->_sprite.setScale(0.5, 0.5);
			MenuItem *topScore_Button = new MenuItem(sf::Vector2f(SCREEN_WIDTH - 230, 20), TOPSCORE, "images/top_score_button.png");
			topScore_Button->_sprite.setScale(0.5, 0.5);

			MenuItem *next_Button = new MenuItem(sf::Vector2f(1050, 650), NEXT, "images/NEXT_button.png", true);
			MenuItem *previous_Button = new MenuItem(sf::Vector2f(150, 650), PREVIOUS, "images/PREV_button.png", true);
			MenuItem *mainLevel = new MenuItem(sf::Vector2f(350, 100), NOTHING, "images/level_1_m.png");
			MenuItem *leftLevel = new MenuItem(sf::Vector2f(50, 200), NOTHING, "images/notMainGame.png");
			MenuItem *rightLevel = new MenuItem(sf::Vector2f(1150, 200), NOTHING, "images/notMainGame.png");
			MenuItem *play_Button = new MenuItem(sf::Vector2f(500, 600), PLAY, "images/PLAY_button.png", true);



			_menuItems.insert(std::pair<std::string, MenuItem*>("play_Button", play_Button));
			_menuItems.insert(std::pair<std::string, MenuItem*>("next_Button", next_Button));
			_menuItems.insert(std::pair<std::string, MenuItem*>("previous_Button", previous_Button));
			_menuItems.insert(std::pair<std::string, MenuItem*>("mainLevel", mainLevel));
			_menuItems.insert(std::pair<std::string, MenuItem*>("leftLevel", leftLevel));
			_menuItems.insert(std::pair<std::string, MenuItem*>("rightLevel", rightLevel));
			_menuItems.insert(std::pair<std::string, MenuItem*>("back_Button", back_Button));
			_menuItems.insert(std::pair<std::string, MenuItem*>("topScore_Button", topScore_Button));

			break;
		}
		case Menu::AEROHOCKEY:
		{
			MenuItem *back_Button = new MenuItem(sf::Vector2f(SCREEN_WIDTH / 2 - 200, 300), BACK, "images/back_button.png");
			MenuItem *topScore_Button = new MenuItem(sf::Vector2f(SCREEN_WIDTH / 2 - 200, 450), TOPSCORE, "images/top_score_button.png");

			_menuItems.insert(std::pair<std::string, MenuItem*>("back_Button", back_Button));
			_menuItems.insert(std::pair<std::string, MenuItem*>("topScore_Button", topScore_Button));
			break;
		}
		case Menu::TERRITORY:
		{
			MenuItem *back_Button = new MenuItem(sf::Vector2f(SCREEN_WIDTH / 2 - 200, 300), BACK, "images/back_button.png");
			MenuItem *topScore_Button = new MenuItem(sf::Vector2f(SCREEN_WIDTH / 2 - 200, 450), TOPSCORE, "images/top_score_button.png");

			_menuItems.insert(std::pair<std::string, MenuItem*>("back_Button", back_Button));
			_menuItems.insert(std::pair<std::string, MenuItem*>("topScore_Button", topScore_Button));
			break;
		}
		default:
			break;
		}
		

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
	Draw();
	playing_Update();
}

void Menu::game_selection_Menu()
{
	Init_GAME_SELECTION();
	Draw();
	game_selection_Menu_Update();

}

void Menu::score_board()
{

}


void Menu::Draw()
{
	_mainWindow.clear(sf::Color(0, 0, 0));
	_mainWindow.draw(background_sprite);

	sf::RectangleShape rectangle(sf::Vector2f(1920, 2));
	rectangle.setPosition(sf::Vector2f(0, 80));
	_mainWindow.draw(rectangle);

	//Game Name on screen top
	std::string name = "";
	switch (_currentGame)
	{
	case Menu::SMASH_IT:
		name = "Smash It";
		break;
	case Menu::TIME_CLIMB:
		name = "Time climb";
		break;
	case Menu::LABYRINTH:
		name = "Labyrinth";
		break;
	case Menu::AEROHOCKEY:
		name = "AeroHockey";
		break;
	case Menu::TERRITORY:
		name = "Territory";
		break;
	default:
		break;
	}
	std::ostringstream nameStr;
	nameStr << name;
	sf::Text text(name, _font, 70);
	text.setPosition(SCREEN_WIDTH / 2 - 150, 0);
	_mainWindow.draw(text);


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



void Menu::playing_Update()
{
	buttonAction clicResult = GetMenuResponse(_mainWindow);

	switch (_currentGame)
	{
	case Menu::SMASH_IT:
		break;
	case Menu::TIME_CLIMB:
		break;
	case Menu::LABYRINTH:
		switch (_currentLabyrinthLevel)
		{
		case Menu::LEVEL_1:
			Get("mainLevel")->_texture.loadFromImage(level_1);

			Get("leftLevel")->_texture.loadFromImage(level_5);
			Get("leftLevel")->_sprite.setTextureRect(Get("mainLevel")->_sprite.getTextureRect());
			Get("leftLevel")->_sprite.setScale(0.3, 0.7);

			Get("rightLevel")->_texture.loadFromImage(level_2);
			Get("rightLevel")->_sprite.setTextureRect(Get("mainLevel")->_sprite.getTextureRect());
			Get("rightLevel")->_sprite.setScale(0.3, 0.7);
			break;
		case Menu::LEVEL_2:
			Get("mainLevel")->_texture.loadFromImage(level_2);

			Get("leftLevel")->_texture.loadFromImage(level_1);
			Get("leftLevel")->_sprite.setTextureRect(Get("mainLevel")->_sprite.getTextureRect());
			Get("leftLevel")->_sprite.setScale(0.3, 0.7);

			Get("rightLevel")->_texture.loadFromImage(level_3);
			Get("rightLevel")->_sprite.setTextureRect(Get("mainLevel")->_sprite.getTextureRect());
			Get("rightLevel")->_sprite.setScale(0.3, 0.7);
			break;
		case Menu::LEVEL_3:
			Get("mainLevel")->_texture.loadFromImage(level_3);

			Get("leftLevel")->_texture.loadFromImage(level_2);
			Get("leftLevel")->_sprite.setTextureRect(Get("mainLevel")->_sprite.getTextureRect());
			Get("leftLevel")->_sprite.setScale(0.3, 0.7);

			Get("rightLevel")->_texture.loadFromImage(level_4);
			Get("rightLevel")->_sprite.setTextureRect(Get("mainLevel")->_sprite.getTextureRect());
			Get("rightLevel")->_sprite.setScale(0.3, 0.7);
			break;
		case Menu::LEVEL_4:
			Get("mainLevel")->_texture.loadFromImage(level_4);

			Get("leftLevel")->_texture.loadFromImage(level_3);
			Get("leftLevel")->_sprite.setTextureRect(Get("mainLevel")->_sprite.getTextureRect());
			Get("leftLevel")->_sprite.setScale(0.3, 0.7);

			Get("rightLevel")->_texture.loadFromImage(level_5);
			Get("rightLevel")->_sprite.setTextureRect(Get("mainLevel")->_sprite.getTextureRect());
			Get("rightLevel")->_sprite.setScale(0.3, 0.7);
			break;
		case Menu::LEVEL_5:
			Get("mainLevel")->_texture.loadFromImage(level_5);

			Get("leftLevel")->_texture.loadFromImage(level_4);
			Get("leftLevel")->_sprite.setTextureRect(Get("mainLevel")->_sprite.getTextureRect());
			Get("leftLevel")->_sprite.setScale(0.3, 0.7);

			Get("rightLevel")->_texture.loadFromImage(level_1);
			Get("rightLevel")->_sprite.setTextureRect(Get("mainLevel")->_sprite.getTextureRect());
			Get("rightLevel")->_sprite.setScale(0.3, 0.7);
			break;
		default:
			break;
		}
		break;
	case Menu::AEROHOCKEY:
		break;
	case Menu::TERRITORY:
		break;
	default:
		break;
	}

	switch (clicResult)
	{
	case Menu::NOTHING:
		break;
	case Menu::PLAY:
		break;
	case Menu::NEXT:
		_currentLabyrinthLevel++;
		if (_currentLabyrinthLevel > 4) _currentLabyrinthLevel = 0;
		break;
	case Menu::PREVIOUS:
		_currentLabyrinthLevel--;
		if (_currentLabyrinthLevel < 0) _currentLabyrinthLevel = 4;
		break;
	case Menu::BACK:
		_menuState = GAME_SELECTION;
		initialized = false;
		break;
	case Menu::TOPSCORE:
		_menuState = SCORE_BOARD;
		initialized = false;
		break;
	default:
		break;
	}

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