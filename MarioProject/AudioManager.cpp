#include "AudioManager.h"

#include <iostream>

AudioManager::AudioManager(std::string musicPath)
{
	m_music_path = musicPath;
	//Loads background music
	LoadMusic();
	LoadSounds();
	//Plays background music
	if (musicPlay)
	{
		if (Mix_PlayingMusic() == 0)
		{
			Mix_PlayMusic(m_music, -1);
		}
	}
}

AudioManager::~AudioManager()
{
	//Clear up music
	Mix_FreeMusic(m_music);
	m_music = nullptr;

	//Free the sound effects
	Mix_FreeChunk(sfx_jump);
	Mix_FreeChunk(sfx_coin);
	Mix_FreeChunk(sfx_hit);
	sfx_jump = nullptr;
	sfx_coin = nullptr;
	sfx_hit = nullptr;
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

void AudioManager::LoadSounds()
{
	//Loads references for each sound effect
	//Jump
	sfx_jump = Mix_LoadWAV("Audio/SFX_smb_jump.wav");
	if (sfx_jump == nullptr)
		std::cout << "Failed to load Jump sound effect. Error: " << Mix_GetError() << std::endl;
	//Coin
	sfx_coin = Mix_LoadWAV("Audio/SFX_smb_coin.wav");
	if (sfx_coin == nullptr)
		std::cout << "Failed to load Coin sound effect. Error: " << Mix_GetError() << std::endl;
	//Enemy Hit
	sfx_hit = Mix_LoadWAV("Audio/SFX_mb_touch.wav");
	if (sfx_hit == nullptr)
		std::cout << "Failed to load Enemy Hit sound effect. Error: " << Mix_GetError() << std::endl;
}

void AudioManager::PlaySound(SOUNDFX soundType)
{
	switch (soundType)
	{
	case JUMP:
		//No specified channel, sound chunk, loop amount
		Mix_PlayChannel(-1, sfx_jump, 0);
		break;
	case COIN:
		Mix_PlayChannel(-1, sfx_coin, 0);
		break;
	case HIT:
		Mix_PlayChannel(-1, sfx_hit, 0);
	}
}