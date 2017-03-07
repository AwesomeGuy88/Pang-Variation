#include "stdafx.h"
#include "SplashScreen.h"
#include <iostream>
#include "Game.h"
#include "ServiceLocator.h"
#include "IAudioProvider.h"


//Show - Loads an image to be displayed on the main window and
//		waits for user interaction before termination
void SplashScreen::Show(sf::RenderWindow& renderWindow)
{
	//Set up SplashScreen Resources
	if (SplashScreen::SetUpScreen())
	{
		return;
	}

	//Runtime of SplashScreen
	while (true)
	{
		FadeIn(renderWindow);	//SplashScreen gradually becomes more opaque

		if (Wait(renderWindow))	//User click moves to main menu immediately
		{
			return;	//Move to main menu immediately
		}
		
		FadeOut(renderWindow); //SplashScreen darkens to black
		
		return;
	}

}


//SetUpScreen() - Sets up screen properties
bool SplashScreen::SetUpScreen(void)
{
	//Set up Opacity
	splashColor.r = 255;
	splashColor.g = 255;
	splashColor.b = 255;
	splashColor.a = 0;
	splashSprite.setColor(splashColor);


	//Set up Sprite Image
	if (splashTexture.loadFromFile("images/SplashScreen.png") != true)
	{
		return true;
	}
	splashSprite.setTexture(splashTexture);

	return false;
}

//FadeIn() - Creates a fade in effect as the splash screen becomes more visible and plays a jingle.
void SplashScreen::FadeIn(sf::RenderWindow& renderWindow)
{

	//Initialise Variables
	float timeCmp = 0;
	bool gameSongPlayed = false;
	IAudioProvider* audioSplash = ServiceLocator::GetAudio();
	Game::clock.restart();

	//Loop until designated time
	while (timeCmp * 51 < 205)
	{
		//Change opacity based on time passed
		timeCmp = Game::clock.getElapsedTime().asSeconds();
		splashColor.a = timeCmp * 51;
		splashSprite.setColor(splashColor);

		//Update the screen
		renderWindow.draw(splashSprite);
		renderWindow.display();

		//Play logo jingle after enough time has passed
		if (timeCmp * 51 > 50 && gameSongPlayed == false)
		{
			gameSongPlayed = true;
			audioSplash->PlaySound("audio/LogoJingle.ogg");
		}

	}


}


//Wait() - Returns true if user has clicked within 2 seconds, else returns false.
bool SplashScreen::Wait(sf::RenderWindow& renderWindow)
{
	//Initialise Variables
	float timeCmp = 0;
	sf::Event event;
	Game::clock.restart();

	//Wait for user interaction for designated time
	while (1)
	{
		renderWindow.pollEvent(event);
		timeCmp = Game::clock.getElapsedTime().asSeconds();

		if (event.type == sf::Event::EventType::KeyPressed
			|| event.type == sf::Event::EventType::MouseButtonPressed
			|| event.type == sf::Event::EventType::Closed)
		{
			return true;
		}

		if (timeCmp > 2.0) {
			break;
		}

	}
	return false;
}


//FadeOut() - Gradually darkens the colour of the sprite until completely black over a period of one second.
void SplashScreen::FadeOut(sf::RenderWindow& renderWindow)
{
	//Initialise Variables
	float timeCmp = 0;
	Game::clock.restart();

	//Continue darkening sprite while rgb values are greater than 1.
	while (255 - timeCmp * 255 > 1)
	{
		timeCmp = Game::clock.getElapsedTime().asSeconds();

		splashColor.r = 255 - timeCmp * 255;
		splashColor.g = 255 - timeCmp * 255;
		splashColor.b = 255 - timeCmp * 255;
		splashSprite.setColor(splashColor);
		renderWindow.draw(splashSprite);
		renderWindow.display();
	}
}
