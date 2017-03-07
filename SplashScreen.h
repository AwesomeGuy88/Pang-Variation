#pragma once

//SplashScreen - A standard splashscreen 

class SplashScreen
{
public:
	void Show(sf::RenderWindow & window);

	bool SetUpScreen(void);
	void FadeIn(sf::RenderWindow& renderWindow);
	bool Wait(sf::RenderWindow& renderWindow);
	void FadeOut(sf::RenderWindow& renderWindow);

private:
	sf::Texture splashTexture;
	sf::Sprite splashSprite;
	sf::Color splashColor;


};