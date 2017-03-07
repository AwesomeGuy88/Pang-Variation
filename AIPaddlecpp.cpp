#pragma once
#include "stdafx.h"
#include "AIPaddle.h"
#include "Game.h"
#include "GameBall.h"


//Constructor - Set sprite properties and load image. (Origin is used for transformations)
AIPaddle::AIPaddle() :
	_velocity(0),
	_maxVelocity(600.0f)
{
	Load("images/paddle.png");
	//assert(IsLoaded());

	GetSprite().setOrigin(GetSprite().getLocalBounds().width / 2, GetSprite().getLocalBounds().height);
}

//Destructor
AIPaddle::~AIPaddle()
{
}

//Draw - Draw the sprite to the window
void AIPaddle::Draw(sf::RenderWindow& rw)
{
	VisibleGameObject::Draw(rw);
}

//GetVelocity - Returns class property _velocity
float AIPaddle::GetVelocity() const
{
	return _velocity;
}

//Update - Get the game ball and check its position with reference to the current location
//		of the paddle. Adjust velocity accordingly to hit the ball, also apply max
//		velocity and wall boundary.
void AIPaddle::Update(float elapsedTime)
{
	//Retrieve game ball
	const GameBall* gameBall = static_cast<GameBall*> (Game::GetGameObjectManager().Get("Ball"));
	sf::Vector2f ballPosition = gameBall->GetPosition();

	//Adjust velocity according to position of paddle and game ball
	if (GetPosition().x - 20 < ballPosition.x)
		_velocity += 15.0f;
	else if (GetPosition().x + 20 > ballPosition.x)
		_velocity -= 10.0f;
	else
		_velocity = 0.0f;

	//Apply maximum velocity
	if (_velocity > _maxVelocity)
		_velocity = _maxVelocity;

	if (_velocity < -_maxVelocity)
		_velocity = -_maxVelocity;


	//Apply wall ricochet
	sf::Vector2f pos = this->GetPosition();

	if (pos.x <= GetSprite().getLocalBounds().width / 2
		|| pos.x >= (Game::SCREEN_WIDTH - GetSprite().getLocalBounds().width / 2))
	{
		_velocity = -_velocity;

		GetSprite().move(_velocity * elapsedTime, 0);
	}

	GetSprite().move(_velocity * elapsedTime, 0);
}




