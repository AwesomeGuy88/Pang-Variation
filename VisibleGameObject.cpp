#include "stdafx.h"
#include "VisibleGameObject.h"

//Constructor - Sets flag of the object	without trigerring default constructor of isLoaded
VisibleGameObject::VisibleGameObject()
	: _isLoaded(false)
{
}

//Destructor - Does nothing, no memory to return to heap or files to close
VisibleGameObject::~VisibleGameObject()
{

}

//Load - Loads specified image to the properties of the object and adjusts relevant
//		flags of the object
void VisibleGameObject::Load(std::string filename)
{
	if (_image.loadFromFile(filename) == false)
	{
		_filename = "";
		_isLoaded = false;
	}
	else
	{
		_filename = filename;
		_sprite.setTexture(_image);
		_isLoaded = true;
		std::cout << "Image Load Success" << std::endl;

	}
}


//Draw - Draws the sprite to the window if conditions are safe.
void VisibleGameObject::Draw(sf::RenderWindow& renderWindow)
{
	if (_isLoaded)
	{
		renderWindow.draw(_sprite);
	}
}

//Update - Update the image in response to user interaction.
void VisibleGameObject::Update(float elapsedTime)
{

}

//SetPosition - Sets the position data of the sprite if conditions are safe.
void VisibleGameObject::SetPosition(float x, float y)
{
	if (_isLoaded)
	{
		_sprite.setPosition(x, y);
	}
}


//GetPosition - Retrieve position from data stored within class
sf::Vector2f VisibleGameObject::GetPosition() const
{
	if (_isLoaded)
	{
		return _sprite.getPosition();
	}
	return sf::Vector2f();
}

//GetSprite - Retrieve sprite stored within class
sf::Sprite& VisibleGameObject::GetSprite()
{
	return _sprite;
}

//IsLoaded - Retrieve _isloaded stored within class
bool VisibleGameObject::IsLoaded() const
{
	return _isLoaded;
}


float VisibleGameObject::GetHeight() const
{
	return _sprite.getLocalBounds().height;
}

float VisibleGameObject::GetWidth() const
{
	return _sprite.getLocalBounds().width;
}

//GetBoundingRect - Using sprite properties, calculates the dimensions of the bounding
//				rectangle and returns it.
sf::Rect<float> VisibleGameObject::GetBoundingRect() const
{
	float width = GetWidth();
	float height = GetHeight();
	sf::Vector2f position = _sprite.getPosition();
	float xPos = position.x;
	float yPos = position.y;

	return sf::Rect<float>(
		xPos,
		yPos,
		width,
		height
		);
}



