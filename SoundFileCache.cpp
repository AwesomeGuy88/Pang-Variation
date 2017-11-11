#include "stdafx.h"
#include "SoundFileCache.h"

//Constructor
SoundFileCache::SoundFileCache(void)
{
}

//Destructor - Use for each to loop through map and call deallocator
SoundFileCache::~SoundFileCache(void)
{
	std::for_each(_sounds.begin(), _sounds.end(), Deallocator<sf::SoundBuffer*>());
	std::for_each(_music.begin(), _music.end(), Deallocator<sf::Music*>());
}


//GetSound - Attempt to find sound in cache and return it. If it does not exist then
//			will attempt to load it as a file and store in the cache.
sf::Sound SoundFileCache::GetSound(std::string soundName) const
{
	std::map<std::string, sf::SoundBuffer*>::iterator itr = _sounds.find(soundName);
	if (itr == _sounds.end()) //Check valid iterator
	{
		sf::SoundBuffer* soundBuffer = new sf::SoundBuffer();
		if (!soundBuffer->loadFromFile(soundName))
		{
			delete soundBuffer;
			throw SoundNotFoundException(soundName + " was not found in call to SoundFileCache::GetSound");
		}

		std::map<std::string, sf::SoundBuffer*>::iterator res =
			_sounds.insert(std::pair<std::string, sf::SoundBuffer*>(soundName, soundBuffer)).first;
		sf::Sound sound;
		sound.setBuffer(*soundBuffer);
		return sound;
	}
	else
	{
		sf::Sound sound;
		sound.setBuffer(*itr->second);
		return sound;
	}

	throw SoundNotFoundException(soundName + " was not found in call to SoundFileCache");
}


//GetSong - Attempt to find music in cache and return it if found. Otherwise check
//		if music can be opened in a file directory, add it to the cache then return it.
sf::Music* SoundFileCache::GetSong(std::string soundName) const
{
	std::map<std::string, sf::Music*>::iterator itr = _music.find(soundName);
	if (itr == _music.end())
	{
		sf::Music* song = new sf::Music();
		if (!song->openFromFile(soundName))
		{
			delete song;
			throw SoundNotFoundException(soundName + " was not found in call to SoundFileCache");
		}
		else
		{
			std::map<std::string, sf::Music*>::iterator res = 
				_music.insert(std::pair<std::string, sf::Music*>(soundName,song)).first;
			return res->second;
		}
	}
	else
	{
		return itr->second;
	}

	throw SoundNotFoundException(soundName + " was not found in call to SoundFileCache");
}


std::map<std::string, sf::SoundBuffer*> SoundFileCache::_sounds;
std::map<std::string, sf::Music*> SoundFileCache::_music;
