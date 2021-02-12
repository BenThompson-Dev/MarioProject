#pragma once
#ifndef _CHARACTERLUIGI_H
#define _CHARACTERLUIGI_H

#include "Character.h"

class CharacterLuigi : public Character
{
public:
	CharacterLuigi(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position);
	virtual void Update(float deltaTime, SDL_Event e);
};

#endif //_CHARACTERLUIGI_H