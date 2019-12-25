#include "Menu.h"

Menu::Menu()
{
	smash_It_image.loadFromFile("images/Smash_It_Game.png");
	time_climb_image.loadFromFile("images/Time_climb_Game.png");
	labyrinth_image.loadFromFile("images/level_5_m.png");
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
	background_sprite.scale(1.5, 1.5);

	
	_font.loadFromFile("font/18123.ttf");

	initialized = false;
}

Menu::~Menu()
{
	std::for_each(_menuItems.begin(), _menuItems.end(), menuItemsDeallocator());
	//delete(client);
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
	_mainWindow.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Menu", sf::Style::Fullscreen);

	_menuState = Menu::GAME_SELECTION;	
	_currentGame = 0;
	_clicData = 0;
	_currentLabyrinthLevel = 0;

	//client = new sClient;
	//client->Init();

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
		

		

		MenuItem *play_Button = new MenuItem(sf::Vector2f(SCREEN_WIDTH / 2 - 208, 900), PLAY_GAMESELECTION, "images/PLAY_button_ru.png", true);
		MenuItem *next_Button = new MenuItem(sf::Vector2f(1530, 900), NEXT, "images/NEXT_button.png", true);
		MenuItem *previous_Button = new MenuItem(sf::Vector2f(160, 900), PREVIOUS, "images/PREV_button.png", true);
		MenuItem *mainGame = new MenuItem(sf::Vector2f(460, 230), NOTHING, "images/Smash_It_Game.png");
		//mainGame->_sprite.setScale(0.7, 0.7);
		MenuItem *leftGame = new MenuItem(sf::Vector2f(100, 330), NOTHING, "images/notMainGame.png");
		MenuItem *rightGame = new MenuItem(sf::Vector2f(1530, 330), NOTHING, "images/notMainGame.png");

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

void Menu::Init_GAME_PREPARATION()
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
			MenuItem *back_Button = new MenuItem(sf::Vector2f(20, 20), BACK, "images/back_button_ru.png");
			back_Button->_sprite.setScale(0.5, 0.5);
			MenuItem *topScore_Button = new MenuItem(sf::Vector2f(SCREEN_WIDTH / 2 - 230, 800), TOPSCORE, "images/top_score_button_ru.png");
			MenuItem* play_Button = new MenuItem(sf::Vector2f(SCREEN_WIDTH / 2 - 230, 350), PLAY_READY, "images/PLAY_button.png");

			//_menuItems.insert(std::pair<std::string, MenuItem*>("play_Button", play_Button));
			_menuItems.insert(std::pair<std::string, MenuItem*>("back_Button", back_Button));
			//_menuItems.insert(std::pair<std::string, MenuItem*>("topScore_Button", topScore_Button));
			break;
		}

		/*case Menu::TIME_CLIMB:
		{
			MenuItem *set_pos_Button = new MenuItem(sf::Vector2f(SCREEN_WIDTH / 2 - 210, 450), SETPOS, "images/set_pos_button.png");
			MenuItem *back_Button = new MenuItem(sf::Vector2f(20, 20), BACK, "images/back_button.png");
			back_Button->_sprite.setScale(0.5, 0.5);
			MenuItem *topScore_Button = new MenuItem(sf::Vector2f(SCREEN_WIDTH / 2 - 210, 600), TOPSCORE, "images/top_score_button.png");
			MenuItem* play_Button = new MenuItem(sf::Vector2f(SCREEN_WIDTH / 2 - 210, 300), PLAY_READY, "images/PLAY_button.png");

			_menuItems.insert(std::pair<std::string, MenuItem*>("play_Button", play_Button));
			_menuItems.insert(std::pair<std::string, MenuItem*>("set_pos_Button", set_pos_Button));
			_menuItems.insert(std::pair<std::string, MenuItem*>("back_Button", back_Button));
			_menuItems.insert(std::pair<std::string, MenuItem*>("topScore_Button", topScore_Button));
			break;
		}*/
		case Menu::LABYRINTH:
		{
			MenuItem *back_Button = new MenuItem(sf::Vector2f(20, 20), BACK, "images/back_button_ru.png");
			back_Button->_sprite.setScale(0.5, 0.5);
			//MenuItem *topScore_Button = new MenuItem(sf::Vector2f(SCREEN_WIDTH - 230, 20), TOPSCORE, "images/top_score_button_ru.png");
			//topScore_Button->_sprite.setScale(0.5, 0.5);

			MenuItem* play_Button = new MenuItem(sf::Vector2f(SCREEN_WIDTH / 2 - 208, 900), PLAY_READY, "images/PLAY_button_ru.png");
			MenuItem* next_Button = new MenuItem(sf::Vector2f(1530, 900), NEXT, "images/NEXT_button.png", true);
			MenuItem* previous_Button = new MenuItem(sf::Vector2f(160, 900), PREVIOUS, "images/PREV_button.png", true);

			MenuItem *mainLevel = new MenuItem(sf::Vector2f(460, 230), NOTHING, "images/level_1_m.png");
			MenuItem *leftLevel = new MenuItem(sf::Vector2f(100, 330), NOTHING, "images/notMainGame.png");
			MenuItem *rightLevel = new MenuItem(sf::Vector2f(1530, 330), NOTHING, "images/notMainGame.png");
		


			_menuItems.insert(std::pair<std::string, MenuItem*>("play_Button", play_Button));
			_menuItems.insert(std::pair<std::string, MenuItem*>("next_Button", next_Button));
			_menuItems.insert(std::pair<std::string, MenuItem*>("previous_Button", previous_Button));
			_menuItems.insert(std::pair<std::string, MenuItem*>("mainLevel", mainLevel));
			_menuItems.insert(std::pair<std::string, MenuItem*>("leftLevel", leftLevel));
			_menuItems.insert(std::pair<std::string, MenuItem*>("rightLevel", rightLevel));
			_menuItems.insert(std::pair<std::string, MenuItem*>("back_Button", back_Button));
			//_menuItems.insert(std::pair<std::string, MenuItem*>("topScore_Button", topScore_Button));

			break;
		}
		case Menu::AEROHOCKEY:
		{
			MenuItem *back_Button = new MenuItem(sf::Vector2f(20, 20), BACK, "images/back_button_ru.png");
			back_Button->_sprite.setScale(0.5, 0.5);
			MenuItem* topScore_Button = new MenuItem(sf::Vector2f(SCREEN_WIDTH / 2 - 190, 500), TOPSCORE, "images/top_score_button_ru.png");
			MenuItem* play_Button = new MenuItem(sf::Vector2f(SCREEN_WIDTH / 2 - 190, 350), PLAY_READY, "images/PLAY_button_ru.png");

			//_menuItems.insert(std::pair<std::string, MenuItem*>("play_Button", play_Button));
			_menuItems.insert(std::pair<std::string, MenuItem*>("back_Button", back_Button));
			//_menuItems.insert(std::pair<std::string, MenuItem*>("topScore_Button", topScore_Button));
			break;
		}
		//case Menu::TERRITORY:
		//{
		//	MenuItem *back_Button = new MenuItem(sf::Vector2f(20, 20), BACK, "images/back_button.png");
		//	back_Button->_sprite.setScale(0.5, 0.5);
		//	MenuItem* topScore_Button = new MenuItem(sf::Vector2f(SCREEN_WIDTH / 2 - 220, 500), TOPSCORE, "images/top_score_button.png");
		//	MenuItem* play_Button = new MenuItem(sf::Vector2f(SCREEN_WIDTH / 2 - 220, 350), PLAY_READY, "images/PLAY_button.png");

		//	//_menuItems.insert(std::pair<std::string, MenuItem*>("play_Button", play_Button));
		//	_menuItems.insert(std::pair<std::string, MenuItem*>("back_Button", back_Button));
		//	//_menuItems.insert(std::pair<std::string, MenuItem*>("topScore_Button", topScore_Button));
		//	break;
		//}
		default:
			break;
		}
		

		initialized = true;
		std::cout << "GAME_PREPARATION initialized";
	}

}

void Menu::Init_SCORE_BOARD()
{
	if (initialized) {
		return;
		
	}
	else
	{
		std::for_each(_menuItems.begin(), _menuItems.end(), menuItemsDeallocator());
		_menuItems.erase(_menuItems.begin(), _menuItems.end());

		MenuItem* back_Button = new MenuItem(sf::Vector2f(SCREEN_WIDTH / 2 - 200, 850), BACK, "images/back_button_ru.png");

		_menuItems.insert(std::pair<std::string, MenuItem*>("back_Button", back_Button));
	}
	initialized = true;
	std::cout << "SCOE_BOARD initialized";

}


void Menu::Init_READY_GAME()
{
	if (initialized) {
		return;

	}
	else
	{
		std::for_each(_menuItems.begin(), _menuItems.end(), menuItemsDeallocator());
		_menuItems.erase(_menuItems.begin(), _menuItems.end());

		MenuItem* back_Button = new MenuItem(sf::Vector2f(SCREEN_WIDTH / 2 - 200, 850), BACK, "images/back_button.png");

		_menuItems.insert(std::pair<std::string, MenuItem*>("back_Button", back_Button));
	}
	initialized = true;
	std::cout << "READY_GAME initialized";

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
		case Menu::GAME_PREPARATION:
		{
			game_preparation();
			break;
		}
	//	case Menu::SCORE_BOARD:
	//	{
	//		score_board();
	//		break;
	//	}
		case Menu::READY_TO_PLAY:
		{
			ready_game();
			break;
		}
	}
	
	_mainWindow.display();
	//client->sendData(makeClientData());
	
}




void Menu::game_preparation()
{
	Init_GAME_PREPARATION();
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
	Init_SCORE_BOARD();
	Draw();
	playing_Update();
}

void Menu::ready_game()
{
	Init_READY_GAME();
	Draw();
	playing_Update();
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
	std::string string_lvl = "";
	//std::string string_topScore = "			TOP Score \n The best five results:";
	sf::String string_topScore(L"5 лучших результатов");
	//std::string topScore_text = "Look at the wall";
	sf::String topScore_text(L"представленны на стене");

	std::string playInfo = "";
	sf::Text playGame_info("", _font, 68);
	


	switch (_currentGame)
	{
	case Menu::SMASH_IT:
		name = "Smash It";
		//playInfo = "Smash the \"Start\" baloon on the wall and game will start \nYou have 60 seconds to smash as many balls as possible \n							use any part of your body";
		playGame_info.setString(L"                                                   Цель игры: \n за 60 секунд лопнуть максимально возможное кол-во шариков.\n Для начала игры лопните большой шарик с надписью \"Играть\".");
		break;
	/*case Menu::TIME_CLIMB:
		playInfo = "Touch the \"Start\" button on the wall and game will start \nTouch all targets in the correct order as fast as you can \n							use any part of your body";
		name = "Time climb";
		break;*/
	case Menu::LABYRINTH:
		//playInfo = "Touch the \"Start\" button on the wall and game will start \n			Touch the \"finish\" button as fast as you can \nwithout touching electrical parts with any part of the body";
		playGame_info.setString(L"		  Игра начнётся после нажатия кнопки \"Старт\" на стене. \n			Доберитесь до кнопки \"Финиш\" за наименьшее время,\n							игнорируя эллектрические участки.");
		name = "Labyrinth";
		switch (_currentLabyrinthLevel)
		{
		case Menu::LEVEL_1:
			string_lvl = "Level 1";
			break;
		case Menu::LEVEL_2:
			string_lvl = "Level 2";
			break;
		case Menu::LEVEL_3:
			string_lvl = "Level 3";
			break;
		case Menu::LEVEL_4:
			string_lvl = "Level 4";
			break;
		case Menu::LEVEL_5:
			string_lvl = "Level 5";
			break;
		default:
			break;
		}
		break;
	case Menu::AEROHOCKEY:
		//playInfo = "		When 2 players touch the square at the same time \n									the game will begin";
		playGame_info.setString(L"												Для начала игры, \n			каждый игрок должен коснуться квадрата на стене. \n						Отбивать шайбу можно руками или ногами.");
		name = "AeroHockey";
		break;
	/*case Menu::TERRITORY:
		playInfo = "		When 2 players touch the square at the same time \n									the game will begin";
		name = "Territory";
		break;*/
	default:
		break;
	}

	sf::Text text(name, _font, 70);
	text.setPosition(SCREEN_WIDTH / 2 - 175, 0);
	_mainWindow.draw(text);

	sf::Text text_lvl(string_lvl, _font, 70);
	text_lvl.setPosition(SCREEN_WIDTH / 2 - 130, 140);
	if (_menuState == GAME_PREPARATION) _mainWindow.draw(text_lvl);

	sf::Text text_topScore(string_topScore, _font, 70);
	text_topScore.setPosition(SCREEN_WIDTH / 2 - 370, 240);
	//if (_menuState == SCORE_BOARD) _mainWindow.draw(text_topScore);

	sf::Text text_topScore_info(topScore_text, _font, 70);
	text_topScore_info.setPosition(SCREEN_WIDTH / 2 - 405, 350);
	//if (_menuState == SCORE_BOARD) _mainWindow.draw(text_topScore_info);

	
	playGame_info.setPosition(0, 300);
	if (_menuState == GAME_PREPARATION && _currentGame != LABYRINTH) _mainWindow.draw(playGame_info);
	if (_menuState == READY_TO_PLAY && _currentGame == LABYRINTH) _mainWindow.draw(playGame_info);


	std::map<std::string, MenuItem*>::iterator it;
	for (it = _menuItems.begin(); it != _menuItems.end(); it++)
	{
		_mainWindow.draw((*it).second->_sprite);
	}	
	
}

void Menu::game_selection_Menu_Update()
{
	buttonAction clicResult = GetMenuResponse(_mainWindow);
	_clicData = clicResult;
	switch (clicResult)
	{
	case Menu::NOTHING:
		break;
	case Menu::PLAY_GAMESELECTION:
		_menuState = GAME_PREPARATION;
		initialized = false;
		break;
	case Menu::NEXT:
		_currentGame++;
		if (_currentGame > 2) _currentGame = 0;
		break;
	case Menu::PREVIOUS:
		_currentGame--;
		if (_currentGame < 0) _currentGame = 2;
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
		//Get("leftGame")->_texture.loadFromImage(territory_image);
		//Get("rightGame")->_texture.loadFromImage(time_climb_image);
		Get("leftGame")->_texture.loadFromImage(aerohockey_image);
		Get("rightGame")->_texture.loadFromImage(labyrinth_image);

		break;
	/*case Menu::TIME_CLIMB:
		Get("mainGame")->_texture.loadFromImage(time_climb_image);
		Get("leftGame")->_texture.loadFromImage(smash_It_image);
		Get("rightGame")->_texture.loadFromImage(labyrinth_image);
		break;*/
	case Menu::LABYRINTH:
		Get("mainGame")->_texture.loadFromImage(labyrinth_image);
		//Get("leftGame")->_texture.loadFromImage(time_climb_image);
		Get("leftGame")->_texture.loadFromImage(smash_It_image);
		Get("rightGame")->_texture.loadFromImage(aerohockey_image);
		break;
	case Menu::AEROHOCKEY:
		Get("mainGame")->_texture.loadFromImage(aerohockey_image);
		Get("leftGame")->_texture.loadFromImage(labyrinth_image);
		//Get("rightGame")->_texture.loadFromImage(territory_image);
		Get("rightGame")->_texture.loadFromImage(smash_It_image);
		break;
	/*case Menu::TERRITORY:
		Get("mainGame")->_texture.loadFromImage(territory_image);
		Get("leftGame")->_texture.loadFromImage(aerohockey_image);
		Get("rightGame")->_texture.loadFromImage(smash_It_image);

		break;*/
	default:
		break;
	}
	Get("leftGame")->_sprite.setTextureRect(Get("mainGame")->_sprite.getTextureRect());
	Get("leftGame")->_sprite.setScale(0.3, 0.7);

	Get("rightGame")->_sprite.setTextureRect(Get("mainGame")->_sprite.getTextureRect());
	Get("rightGame")->_sprite.setScale(0.3, 0.7);


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		bool flag = true;
		int a = AUTO_COLIBRATION * 1000 + _currentGame * 100 + NOTHING * 10;
		//client->sendData(a);

		while (flag)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
			{
				flag = false;
			}
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
	{
		bool flag = true;
		int a = MANUAL_COLIBRATION * 1000 + _currentGame * 100 + 1 * 10; //1 - start manualeqasion colibration
		//client->sendData(a);

		while (flag)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num0))
			{
				//client->sendData(0);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
			{
				//client->sendData(1);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
			{
				//client->sendData(2);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
			{
				//client->sendData(3);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4))
			{
				//client->sendData(4);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num5))
			{
				//client->sendData(5);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num6))
			{
				//client->sendData(6);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num7))
			{
				//client->sendData(7);
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
			{
				flag = false;
			}
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		bool flag = true;
		int a = MANUAL_COLIBRATION * 1000 + _currentGame * 100 + 0 * 10; //1 - start manualeqasion colibration
		//client->sendData(a);

		while (flag)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::B))
			{
				flag = false;
			}
		}
	}
}



void Menu::playing_Update()
{
	

	buttonAction clicResult = GetMenuResponse(_mainWindow);
	_clicData = clicResult;

	switch (_currentGame)
	{
	case Menu::SMASH_IT:
		break;
	/*case Menu::TIME_CLIMB:
		break;*/
	case Menu::LABYRINTH:
		if (_menuState == GAME_PREPARATION)
		{
			switch (_currentLabyrinthLevel)
			{
			case Menu::LEVEL_1:
				Get("mainLevel")->_texture.loadFromImage(level_1);
				Get("leftLevel")->_texture.loadFromImage(level_5);
				Get("rightLevel")->_texture.loadFromImage(level_2);
				break;
			case Menu::LEVEL_2:
				Get("mainLevel")->_texture.loadFromImage(level_2);
				Get("leftLevel")->_texture.loadFromImage(level_1);
				Get("rightLevel")->_texture.loadFromImage(level_3);
				break;
			case Menu::LEVEL_3:
				Get("mainLevel")->_texture.loadFromImage(level_3);
				Get("leftLevel")->_texture.loadFromImage(level_2);
				Get("rightLevel")->_texture.loadFromImage(level_4);
				break;
			case Menu::LEVEL_4:
				Get("mainLevel")->_texture.loadFromImage(level_4);
				Get("leftLevel")->_texture.loadFromImage(level_3);
				Get("rightLevel")->_texture.loadFromImage(level_5);
				break;
			case Menu::LEVEL_5:
				Get("mainLevel")->_texture.loadFromImage(level_5);
				Get("leftLevel")->_texture.loadFromImage(level_4);
				Get("rightLevel")->_texture.loadFromImage(level_1);
				break;
			default:
				break;
			}
			Get("leftLevel")->_sprite.setTextureRect(Get("mainLevel")->_sprite.getTextureRect());
			Get("leftLevel")->_sprite.setScale(0.3, 0.7);
			Get("rightLevel")->_sprite.setTextureRect(Get("mainLevel")->_sprite.getTextureRect());
			Get("rightLevel")->_sprite.setScale(0.3, 0.7);
		}
		
		break;
	case Menu::AEROHOCKEY:
		break;
	/*case Menu::TERRITORY:
		break;*/
	default:
		break;
	}

	switch (clicResult)
	{
	case Menu::NOTHING:
		break;
	case Menu::PLAY_READY:
		_menuState = READY_TO_PLAY;
		initialized = false;
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
		//if (_menuState == SCORE_BOARD) _menuState = GAME_PREPARATION;
		if (_menuState == READY_TO_PLAY) _menuState = GAME_PREPARATION;
		else _menuState = GAME_SELECTION;
		initialized = false;
		//sendData();
		break;
	//case Menu::TOPSCORE:
		//_menuState = SCORE_BOARD;
	//	initialized = false;
	//	break;
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


Menu::MenuItem* Menu::Get(std::string name) const
{
	std::map<std::string, Menu::MenuItem*>::const_iterator results = _menuItems.find(name);
	if (results == _menuItems.end())
		return NULL;
	return results->second;
}


int Menu::makeClientData()
{
	int a = _menuState * 1000 + _currentGame*100 + _clicData*10 + _currentLabyrinthLevel;
	return a;
}
