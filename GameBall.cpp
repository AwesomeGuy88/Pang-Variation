#include "stdafx.h"
#include "GameBall.h"
#include "Game.h"

//Constructor - Loads image, sets sprite properties
GameBall::GameBall() :
	_velocity(230.0f),
	_elapsedTimeSinceStart(0.0f)
{
	
	Load("images/ball.png");
	//assert(IsLoaded());
	GetSprite().setOrigin(15, 15);

	srand(time(NULL));
	_angle = rand() % 360;
}


//Destructor
GameBall::~GameBall()
{
}


//Update - Keeps track of elapsed time, calculates movement while also considering
//		wall collisions, paddle collisions and boundaries.
void GameBall::Update(float elapsedTime)
{
	_elapsedTimeSinceStart += elapsedTime;

	//Delay start of game until 3 seconds have passed
	if (_elapsedTimeSinceStart < 3.0f)
		return;

	//std::cout << "test" << std::endl;
	//Use elapsed time for initial calculations of movement
	float moveAmount = _velocity * elapsedTime;

	float moveByX = LinearVelocityX(_angle) * moveAmount;
	float moveByY = LinearVelocityY(_angle) * moveAmount;



	//Collide with wall
	//	If the ball collides with the wall then calculate a ricochet off the wall
	if (GetPosition().x + moveByX <= 0 + GetWidth() / 2
		|| GetPosition().x + GetHeight() / 2 + moveByX >= Game::SCREEN_WIDTH)
	{
		_angle = 360.0f - _angle;
		if (_angle > 260.0f && _angle < 280.0f) _angle += 20.0f;
		if (_angle > 80.0f && _angle < 100.0f) _angle += 20.0f;
		moveByX = -moveByX;
	}


	//Collide with paddle
	//	If the ball collides with the paddle, then calculate a ricochet off the paddle
	//	based on the paddle velocity
	PlayerPaddle* player1 =
		dynamic_cast<PlayerPaddle*>(Game::GetGameObjectManager().Get("Paddle1"));

	if (player1 != NULL)
	{
		sf::Rect<float> p1BB = player1->GetBoundingRect();

		if (p1BB.intersects(GetBoundingRect()))
		{
			_angle = 360.0f - (_angle - 180.0f);
			if (_angle > 360.0f) _angle -= 360.0f;

			moveByY = -moveByY;

			//Make sure ball is not within paddle
			if (GetBoundingRect().top - GetBoundingRect().height > player1->GetBoundingRect().top)
			{
				SetPosition(GetPosition().x, player1->GetBoundingRect().top - GetWidth() / 2 - 1);
			}

			//Ball affected by player velocity
			//	Angle adjustments based on the direction of paddle movement
			float playerVelocity = player1->GetVelocity();

			if (playerVelocity < 0)
			{
				//Moving left
				_angle -= 20.0f;
				if (_angle < 0) _angle = 360.0f - _angle;
			}
			else if (playerVelocity > 0)
			{
				_angle += 20.0f;
				if (_angle > 360.0f) _angle = _angle - 360.0f;
			}

			_velocity += 5.0f;

		}

		//Ball does not leave through bottom wall.
		if (GetPosition().y - GetHeight() / 2 <= 0)
		{
			_angle = 180 - _angle;
			moveByY = -moveByY;
		}

		//Ball does not leave through top wall
		if (GetPosition().y + GetHeight() / 2 + moveByY >= Game::SCREEN_HEIGHT)
		{
			//Move to middle of screen and randomise angle
			GetSprite().setPosition(Game::SCREEN_WIDTH / 2, Game::SCREEN_HEIGHT);
			srand(time(NULL));
			_angle = rand() % 360;
			_velocity = 220.0f;
			_elapsedTimeSinceStart = 0.0f;
		}

		GetSprite().move(moveByX, moveByY); //Assign calculated movement
	}

}

//LinearVelocityX - Calculates the x component of the trajectory of the ball based off angle
float GameBall::LinearVelocityX(float angle)
{
	angle -= 90;
	if (angle < 0) angle = 360 + angle;
	return (float)std::cos(angle * (3.1415926 / 180.0f));
}

//LinearVeloctyY - Calculates the y component of the trajectory of the ball based off angle
float GameBall::LinearVelocityY(float angle)
{
	angle -= 90;
	if (angle < 0) angle = 360 + angle;
	return (float)std::sin(angle*(3.1415926 / 180.0f));
}




//Note: We have used a dynamic cast, if called on an object which is incapable of being
//	casted to the type we desire then it will instead return null. (Checking if the cast
//	is okay to perform)