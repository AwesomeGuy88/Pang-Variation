#include "stdafx.h"
#include "MainMenu.h"



//Show - Set up menu image, clickable regions, actions and waits for user interaction
//		by passing control to another member function.
MainMenu::MenuResult MainMenu::Show(sf::RenderWindow& window)
{

	//Load menu image
	sf::Texture image;
	image.loadFromFile("images/mainmenu.png");
	sf::Sprite sprite(image);

	//Setup Clickable regions

	//Play menu item coordinates
	MenuItem playButton;
	playButton.rect.top = 145;
	playButton.rect.left = 0;
	playButton.rect.height = 235;
	playButton.rect.width = 1023;
	playButton.action = Play;

	//ExitMenu item coordinates
	MenuItem exitButton;
	exitButton.rect.top = 383;
	exitButton.rect.left = 0;
	exitButton.rect.height = 180;
	exitButton.rect.width = 1023;
	exitButton.action = Exit;

	_menuItems.push_back(playButton);
	_menuItems.push_back(exitButton);

	window.draw(sprite);
	window.display();

	return GetMenuResponse(window);

}

//HandleClick - By using the location of the mouse click, determines the appropriate
//				action to pass back to caller. Achieved by cycling through dimensions
//				of menu items and comparing against click location
MainMenu::MenuResult MainMenu::HandleClick(int x, int y)
{
	std::list<MenuItem>::iterator it;

	//Traverse through items in menu
	for (it = _menuItems.begin(); it != _menuItems.end(); it++) {
		sf::Rect<int> menuItemRect = (*it).rect;
		//Check that click is within menuItem boundaries
		if ((menuItemRect.height + menuItemRect.top) > y
			&& menuItemRect.top < y
			&& menuItemRect.left < x
			&& (menuItemRect.width + menuItemRect.left) > x)
		{
			////////////////////////////////////////////////////
			std::cout << "Menu Item Click Detected" << (*it).action << std::endl;
			////////////////////////////////////////////////////
			return (*it).action;
		}
	}

	return Nothing;
}

//GetMenuResponse - Waits for an event of the relevant type before passing control
//				to another member function to determine the appropriate reponse.
MainMenu::MenuResult MainMenu::GetMenuResponse(sf::RenderWindow& window)
{
	sf::Event menuEvent;

	while (true)
	{
		while (window.waitEvent(menuEvent))
		{
			if (menuEvent.type == sf::Event::MouseButtonPressed)
			{
				return HandleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
			}
			if (menuEvent.type == sf::Event::Closed)
			{
				return Exit;
			}
		}
	}
}


