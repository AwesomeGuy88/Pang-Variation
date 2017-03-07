#include "stdafx.h"
#include "GameObjectManager.h"
#include "Game.h"

//Constructor - does nothing
GameObjectManager::GameObjectManager() 
{
	//t2 = Game::clock.getElapsedTime();
}

//Destructor - Loops through all game objects and runs the deallocator 
//				Uses the for_each method to loop which takes two iterators and a unary function
GameObjectManager::~GameObjectManager()
{
	std::for_each(_gameObjects.begin(), _gameObjects.end(), GameObjectDeallocator());
}

//Add - Adds an identifier (name) and data (gameObject) to the map structure
void GameObjectManager::Add(std::string name, VisibleGameObject* gameObject)
{
	_gameObjects.insert(std::pair<std::string, VisibleGameObject*>(name, gameObject));
}

//Remove - Set an iterator to the specified key-data combination and uses this to delete it
//		using map API if pointer is valid (does not point to the special value EOF at
//		at the end of the map) and remove the combination from the map.
void GameObjectManager::Remove(std::string name)
{
	std::map<std::string, VisibleGameObject*>::iterator	results = _gameObjects.find(name);
	if (results != _gameObjects.end())
	{
		delete results->second;	//Delete the VisibleGameObject component of the map
		_gameObjects.erase(results);
	}
}


//Get - Sets up an iterator to point to the specified identifier and uses this to
//		return the VisibleGameObject pointer.
VisibleGameObject* GameObjectManager::Get(std::string name) const
{
	std::map<std::string, VisibleGameObject*>::const_iterator results = _gameObjects.find(name);
	if (results == _gameObjects.end())
		return NULL;
	return results->second;
}

//GetObjectCount - returns the number of gameObjects recorded within the map using 
//				standard map API
int GameObjectManager::GetObjectCount() const
{
	return _gameObjects.size();
}

//DrawAll - Sets up an iterator and uses this to loop through the map and draw each
//			of the visible game objects
void GameObjectManager::DrawAll(sf::RenderWindow& renderWindow)
{
	std::map<std::string, VisibleGameObject*>::const_iterator itr = _gameObjects.begin();
	while (itr != _gameObjects.end())
	{
		itr->second->Draw(renderWindow);
		itr++;
	}
}

//UpdateAll - Invokes Update function of all objects by retrieving and passing the time
void GameObjectManager::UpdateAll()
{
	std::map<std::string, VisibleGameObject*>::const_iterator itr = _gameObjects.begin();

	sf::Time t1 = Game::clock.getElapsedTime();
	t1 = t1 - t2; //Get the time since that last update
	float timeDelta = t1.asSeconds();

	while (itr != _gameObjects.end())
	{
		itr->second->Update(timeDelta);
		itr++;
	}

	t2 = t2 + t1;
}






