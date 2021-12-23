#pragma once
#ifndef _CHARACTERLUIGI_H
#define _CHARACTERLUIGI_H

#include "Character.h"
#include "AudioManager.h"

class CharacterLuigi : public Character
{
private:
	AudioManager* m_audio_manager;
public:
	CharacterLuigi(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map, AudioManager* audioManager);
	virtual void Update(float deltaTime, SDL_Event e);
};

#endif //_CHARACTERLUIGI_H