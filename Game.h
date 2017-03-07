
#pragma once									   //Code is only included once
#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"
#include "PlayerPaddle.h"
#include "GameObjectManager.h"

//Game - The game class divides runtime into different states that give us a
//		better understanding of the code and the ability to departmentalise it.

class Game
{

public:
	static void Start();

	static sf::RenderWindow& GetWindow();
	static GameObjectManager& GetGameObjectManager();

	static sf::Clock clock;

	const static int SCREEN_WIDTH = 1024;
	const static int SCREEN_HEIGHT = 768;

private:
	static bool IsExiting();
	static void GameLoop();

	static void ShowSplashScreen();
	static void ShowMenu();

	enum GameState { Uninitialized, ShowingSplash, Paused, ShowingMenu,
	Playing, Exiting};

	static GameState _gameState;
	static sf::RenderWindow _mainWindow;

	static GameObjectManager _gameObjectManager;
};

//Static class:
// Used for the purpose of a cleaner solution, requiring no instantiation or destruction
// of object.