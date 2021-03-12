#include "AudioManager.h"

#include <iostream>

AudioManager::AudioManager(std::string musicPath)
{
	m_music_path = musicPath;
	//Loads background music
	LoadMusic();
	if (Mix_PlayingMusic() == 0)
	{
		Mix_PlayMusic(m_music, -1);
	}
}

AudioManager::~AudioManager()
{
	//Clear up music
	Mix_FreeMusic(m_music);
	m_music = nullptr;
}

void AudioManager::LoadMusic()
{
	//Loads the music from the given file path
	m_music = Mix_LoadMUS(m_music_path.c_str());
	{
		if (m_music == nullptr)
		{
			std::cout << "Failed to load music. Error: " << Mix_GetError() << std::endl;
		}
	}
}