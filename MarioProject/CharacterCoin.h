#pragma once
#ifndef _CHARACTERCOIN_H
#define _CHARACTERCOIN_H

#include "Character.h"
#include "constants.h"
#include <string>

class CharacterCoin : public Character
{
private:
	float m_single_sprite_w;
	float m_single_sprite_h;

	FACING m_facing_direction;
	float m_movement_speed;

	float m_frame_delay;
	int m_current_frame;
public:
	CharacterCoin(SDL_Renderer* renderer, std::string imagePath, LevelMap* map, Vector2D start_position, FACING start_facing, float movement_speed);
	~CharacterCoin();

	void Jump();

	virtual void Render(float deltaTime);
	virtual void Update(float deltaTime, SDL_Event e);
};

#endif //_CHARACTERCOIN_H