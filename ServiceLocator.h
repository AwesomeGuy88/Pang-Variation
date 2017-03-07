#pragma once
#include "stdafx.h"
#include "IAudioProvider.h"

//Service Locator - Provides the audio service to the game, as part of the Service
//			Locator pattern. This is done for coupling and reusability of code.

class ServiceLocator
{
public:
	static IAudioProvider* GetAudio() { return _audioProvider; } const
	static void RegisterServiceLocator(IAudioProvider* provider)
	{
		_audioProvider = provider;
	}

private:
	static IAudioProvider* _audioProvider;
};