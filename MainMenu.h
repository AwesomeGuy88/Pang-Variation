#pragma once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include <list>


//MainMenu - Code required for a standard responsive main menu

class MainMenu
{

public:
	enum MenuResult { Nothing, Exit, Play };

	struct MenuItem
		{
		public:
			sf::Rect<int> rect;	  //Rect is a templated class
			MenuResult action;
		};

	MenuResult Show(sf::RenderWindow& window);

private:
	MenuResult GetMenuResponse(sf::RenderWindow& window);
	MenuResult HandleClick(int x, int y);
	std::list<MenuItem> _menuItems;
};