#include "stdafx.h"
#include "Game.h"
#include "SplashScreen.h"
#include "MainMenu.h"
#include "GameBall.h"
#include "SFMLSoundProvider.h"
#include "ServiceLocator.h"
#include "IAudioProvider.h"
#include "AIPaddle.h"




//Start - Section of code which prepares the game before running repetitive and looping
//		code in the game loop. This includes creating a window, setting up sprites and
//		passing an initial gamestate before looping.
void Game::Start(void)
{
	if (_gameState != Uninitialized)
		return;

	
	_mainWindow.create(sf::VideoMode(1024, 768, 32), "Pang!");

	PlayerPaddle *_player1 = new PlayerPaddle();
	_player1->SetPosition((1024 / 2) - 45, 700);
	_gameObjectManager.Add("Paddle1", _player1);

	AIPaddle* player2 = new AIPaddle();
	player2->SetPosition((SCREEN_WIDTH / 2), 40);
	_gameObjectManager.Add("Paddle2", player2);

	GameBall *ball = new GameBall();
	ball->SetPosition((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2)-15);
	_gameObjectManager.Add("Ball", ball);

	_gameState = Game::ShowingSplash;

	SFMLSoundProvider soundProvider;
	ServiceLocator::RegisterServiceLocator(&soundProvider);

	while (!IsExiting())
	{
		GameLoop();
	}

	_mainWindow.close();
}


//IsExiting - Section of the code which checks that the gamestate indicates whether
//			it should be exiting
bool Game::IsExiting()
{
	if (_gameState == Game::Exiting)
		return true;
	else
		return false;

}

//GameLoop - Section of the code which is repetitively checking and responding to events
//			This section is further divided to the different gamestates; showingsplash,
//			shwoingmenu and playing. It extends on this by dividing the desired functionality
//			of each gamestate.
void Game::GameLoop()
{
	sf::Event currentEvent;
	_mainWindow.pollEvent(currentEvent);


	switch (_gameState)
	{
		case Game::ShowingSplash:
		{
			ShowSplashScreen();
			break;
		}
		case Game::ShowingMenu:
		{
			ShowMenu();
			break;
		}
		case Game::Playing:
		{
			_mainWindow.clear(sf::Color(0, 0, 0));

			_gameObjectManager.UpdateAll();
			_gameObjectManager.DrawAll(_mainWindow);

			_mainWindow.display();

			if (currentEvent.type == sf::Event::Closed)
			{
				_gameState = Game::Exiting;
			}
			if (currentEvent.type == sf::Event::KeyPressed)
			{
				if (currentEvent.key.code == sf::Keyboard::Escape) 
					ShowMenu();
			}
				
			break;
		}
	}
	

}

//ShowSplashScreen - Runs the required code to create a responsive splashscreen and 
//				changes the gamestate to showingmenu upon completion.
void Game::ShowSplashScreen()
{
	SplashScreen splashScreen;
	splashScreen.Show(_mainWindow);
	_gameState = Game::ShowingMenu;

}

//ShowMenu - Runs the required code to create a responsive menu, determining the response
//			based on user mouseclick locations
void Game::ShowMenu()
{
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(_mainWindow);
	ServiceLocator::GetAudio()->PlaySong("audio/song.ogg", false);
	//Change gamestate based on user-click
	std::cout << "result: " << result << std::endl;
	switch (result)
	{
	case MainMenu::Exit:
		std::cout << "entered exit state" << std::endl;
		_gameState = Game::Exiting;
		break;
	case MainMenu::Play:
		clock.restart();
		std::cout << "Entered Play State" << std::endl;
		_gameState = Game::Playing;
		break;
	}

}

//GetWindow - Retrieve mainWindow
sf::RenderWindow& Game::GetWindow()
{
	return _mainWindow;
}

//GetGameObjectManger - Retrieve object manager
GameObjectManager& Game::GetGameObjectManager()
{
	return _gameObjectManager;
}

//Initialising static variables within Game Class (standard practice)
Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
GameObjectManager Game::_gameObjectManager;
sf::Clock Game::clock;



