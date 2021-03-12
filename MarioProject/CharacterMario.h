#pragma once
#ifndef _CHARACTERMARIO_H
#define _CHARACTERMARIO_H

#include "Character.h"
#include "AudioManager.h"

class CharacterMario : public Character
{
private:
	AudioManager* m_audio_manager;
public:
	CharacterMario(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map, AudioManager* audio_manager);
	virtual void Update(float deltaTime, SDL_Event e);
};

#endif //_CHARACTERMARIO_H