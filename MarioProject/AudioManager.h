#pragma once
#ifndef _AUDIOMANAGER_H
#define _AUDIOMANAGER_H

#include <SDL.h>
#include <SDL_mixer.h>
#include <string>

#include "Commons.h"

class AudioManager
{
private:
	//Music reference
	Mix_Music* m_music = nullptr;
	//SFX references
	Mix_Chunk* sfx_jump = nullptr;
	Mix_Chunk* sfx_coin = nullptr;
	Mix_Chunk* sfx_hit = nullptr;

	std::string m_music_path;

	//Used to disable music so it doesn't get annoying when testing
	bool musicPlay = false;

	void LoadMusic();
	void LoadSounds();
public:
	AudioManager(std::string musicPath);
	~AudioManager();

	void PlaySound(SOUNDFX soundType);
};

#endif //_AUDIOMANAGER_H