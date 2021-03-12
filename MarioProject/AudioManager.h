#pragma once
#ifndef _AUDIOMANAGER_H
#define _AUDIOMANAGER_H

#include <SDL.h>
#include <SDL_mixer.h>
#include <string>

class AudioManager
{
private:
	//Music reference
	Mix_Music* m_music = nullptr;
	std::string m_music_path;
	//Sound effect references

	void LoadMusic();
public:
	AudioManager(std::string musicPath);
	~AudioManager();

	void PlaySound(std::string soundType);
};

#endif //_AUDIOMANAGER_H