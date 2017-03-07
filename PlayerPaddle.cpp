#include "stdafx.h"
#include "PlayerPaddle.h"
#include "Game.h"

//Constructor - Sets class variables, image and sprite properties.
PlayerPaddle::PlayerPaddle() :
_velocity(0), _maxVelocity(600.0f)
{
	Load("images/paddle.png");
	//assert(IsLoaded());

	//Set Center point
	GetSprite().setOrigin(GetSprite().getLocalBounds().width / 2, GetSprite().getLocalBounds().height / 2);
}

PlayerPaddle::~PlayerPaddle()
{
}

//Draw - Draws the paddle to the main window
void PlayerPaddle::Draw(sf::RenderWindow& rw)
{
	VisibleGameObject::Draw(rw);
}

//GetVelocity - Retrieve class variable
float PlayerPaddle::GetVelocity() const
{
	return _velocity;
}

//Update - Get user input and calculate variables based on this. Apply restrictions on
//			calculations and apply changes using move()
void PlayerPaddle::Update(float elapsedTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		_velocity -= 3.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		_velocity += 3.0f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		_velocity = 0.0f;
	}

	if (_velocity > _maxVelocity)
		_velocity = _maxVelocity;

	if (_velocity < -_maxVelocity)
		_velocity = -_maxVelocity;

	sf::Vector2f pos = this->GetPosition();

	if (pos.x < GetSprite().getLocalBounds().width / 2
		|| pos.x >(1024 - GetSprite().getLocalBounds().width / 2))
	{
		_velocity = -_velocity; //Bounce off wa
	}

	GetSprite().move(_velocity * elapsedTime, 0);


}

