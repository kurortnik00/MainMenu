#pragma once
#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include <list>
#include <sstream>
#include <iostream>

class Menu
{

public:
	Menu();
	~Menu();

	void Start();
	

	sf::RenderWindow& GetWindow();
	
	
	

private:
	//void Init();
	void MenuLoop();
	void Init_GAME_SELECTION();
	void Init_SCORE_BOARD();
	void Init_PLAYING();

	bool initialized;
	
	const int SCREEN_WIDTH = 1366;
	const int SCREEN_HEIGHT = 768;
	bool IsExiting();
	sf::RenderWindow _mainWindow;

	sf::Image background_image;
	sf::Texture background_texture;
	sf::Sprite background_sprite;


	enum menuState { 
		EXITING, PLAYING, SCORE_BOARD, GAME_SELECTION 
	};
	enum games {
		SMASH_IT, TIME_CLIMB, LABYRINTH, AEROHOCKEY, TERRITORY
	};
	enum buttonAction{
		NOTHING, PLAY, NEXT, PREVIOUS, BACK, TOPSCORE, SETPOS, EXIT
	};
	enum levels
	{
		LEVEL_1, LEVEL_2, LEVEL_3, LEVEL_4, LEVEL_5
	};


	struct MenuItem
	{
	public:
		MenuItem(sf::Vector2f position, buttonAction action, std::string fileName, bool maskFromCollor);
		void Move(sf::Vector2f pos);
		sf::Vector2f _position;
		buttonAction _action;
		sf::Rect<int> _rect;
		sf::Image _image;
		sf::Texture _texture;
		sf::Sprite _sprite;
		float animationTime;
		sf::Clock animationClock;
		int animationFrame;
		sf::Vector2f _center;
	};


	buttonAction GetMenuResponse(sf::RenderWindow& window);
	buttonAction HandleClick(sf::RenderWindow& window, int x, int y);


	menuState _menuState;
	int _currentGame;
	int _currentLabyrinthLevel;
	std::map<std::string, MenuItem*> _menuItems;
	sf::Vector2f velocity;

	float dist2(sf::Vector2f const & p1, sf::Vector2f const & p2);
	void playing();
	void game_selection_Menu();
	void score_board();


	void Draw();
	void game_selection_Menu_Update();

	void playing_Update();

	struct menuItemsDeallocator
	{
		void operator()(const std::pair < std::string, MenuItem*> & p) const
		{
			delete p.second;
		}
	};
	Menu::MenuItem* Get(std::string name) const;

	sf::Font _font;

	sf::Image smash_It_image;
	sf::Image time_climb_image;
	sf::Image labyrinth_image;
	sf::Image aerohockey_image;
	sf::Image territory_image;

	sf::Image level_1;
	sf::Image level_2;
	sf::Image level_3;
	sf::Image level_4;
	sf::Image level_5;


};