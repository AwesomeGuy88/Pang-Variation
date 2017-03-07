#include "stdafx.h"
#include "SFMLSoundProvider.h"
#include "SoundFileCache.h"


//Constructor - Initialise empty variables
SFMLSoundProvider::SFMLSoundProvider() :
_currentSongName("")
{
}


//PlaySound - Find an unoccupied sound channel and play sound. 
void SFMLSoundProvider::PlaySound(std::string filename)
{
	int availChannel = -1;


	//Find an available Channel
	for (int i = 0; i < MAX_SOUND_CHANNELS; i++)
	{
		if (_currentSounds[i].getStatus() != sf::Sound::Playing)
		{
			availChannel = i;
			break;
		}
	}

	//If sound channels are in use, do nothing.
	if (availChannel != -1)
	{
		try
		{
			_currentSounds[availChannel] = _soundFileCache.GetSound(filename);
			_currentSounds[availChannel].play();
		}
		catch (SoundNotFoundException& snfe)
		{
			//File not found, does nothing.
		}
	}

}


//PlaySong - Load song, stop previous song and play current song
void SFMLSoundProvider::PlaySong(std::string filename, bool looping)
{
	sf::Music* currentSong;
	try
	{
		currentSong = _soundFileCache.GetSong(filename);
	}
	catch (SoundNotFoundException&)
	{
		//Exit since file cant be loaded
		return;
	}

	//Stop previous song
	if (_currentSongName != "")
	{
		try
		{
			sf::Music* priorSong = _soundFileCache.GetSong(_currentSongName);
			if (priorSong->getStatus() != sf::Sound::Stopped)
			{
				priorSong->stop();
			}
		}
		catch (SoundNotFoundException&)
		{
			//Do nothing
		}
	}
	_currentSongName = filename;
	currentSong->setLoop(looping);
	currentSong->play();

}

//StopAllSounds - Stop music and sounds if playing
void SFMLSoundProvider::StopAllSounds()
{
	for (int i = 0; i < MAX_SOUND_CHANNELS; i++)
	{
		_currentSounds[i].stop();
	}

	if (_currentSongName != "")
	{
		sf::Music* currentSong = _soundFileCache.GetSong(_currentSongName);
		if (currentSong->getStatus() == sf::Sound::Playing)
		{
			currentSong->stop();
		}
	}

}

//IsSoundPlaying - Checks whether sound is playing by looping through channels
bool SFMLSoundProvider::IsSoundPlaying()
{
	for (int i = 0; i < MAX_SOUND_CHANNELS; i++)
	{
		if (_currentSounds[i].getStatus() == sf::Sound::Playing)
			return true;
	}
	return false;
}

//IsSongPlaying - CHecks whether song is playing
bool SFMLSoundProvider::IsSongPlaying()
{
	if (_currentSongName != "")
	{
		return _soundFileCache.GetSong(_currentSongName)->getStatus() == sf::Music::Playing;
	}
	return false;
}
