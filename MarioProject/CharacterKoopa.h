#pragma once
#ifndef _CHARACTERKOOPA_H
#define _CHARACTERKOOPA_H

#include "Character.h"
#include <string>

class CharacterKoopa : public Character
{
private:
	float m_single_sprite_w;
	float m_single_sprite_h;
	bool m_injured;
	float m_injured_time;

	FACING m_facing_direction;
	float m_movement_speed;

	void FlipRightWayUp();
public:
	CharacterKoopa(SDL_Renderer* renderer, std::string imagePath, LevelMap* map, Vector2D start_position, FACING start_facing, float movement_speed);
	~CharacterKoopa();

	void TakeDamage();
	void Jump();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);

	bool GetInjured() { return m_injured; }
};

#endif //_CHARACTERKOOPA_H