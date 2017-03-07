#pragma once
#include "VisibleGameObject.h"



//GameObjectManager - In charge of updating, drawing and removing all visible game
//				objects. Particularly useful for larger scale games.

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();

	void Add(std::string name, VisibleGameObject* gameObject);
	void Remove(std::string name);
	int GetObjectCount() const;
	VisibleGameObject* Get(std::string name) const;

	void DrawAll(sf::RenderWindow& renderWindow);
	void UpdateAll();

private:
	std::map<std::string, VisibleGameObject*> _gameObjects;
	sf::Time t2;

	//Functor
	// Object created that overloads the function call operator by defining operator()
	// and works in conjunction with for each, which passes it the necessary arguments.
	struct GameObjectDeallocator
	{
		void operator()(const std::pair <std::string, VisibleGameObject*>& p) const
		{
			delete p.second;
		}
	};
};


//Note: Contains map, which is a structure containing data linked with an
//		identifier. In this case the identifier will be the name and the data
//		will be the visiblegameobject
//		Maps are composed of std::pair<> objects which is simply two objects
//		mashed together




