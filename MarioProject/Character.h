#pragma once
#ifndef _CHARACTER_H
#define _CHARACTER_H

#include <SDL.h>
#include <iostream>
#include <string>
#include "Commons.h"
#include "Texture2D.h"
#include "LevelMap.h"

class Texture2D; //Forward declares Texture2D

class Character
{
protected:
	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;
	std::string m_image;
	bool m_moving_left;
	bool m_moving_right;
	//Jump variables
	bool m_jumping;
	bool m_can_jump;
	float m_jump_force;
	//Protected functions
	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
	virtual void Jump(float deltaTime);
	virtual void AddGravity(float deltaTime);
	//Collision variable
	float m_collision_radius;
private:
	FACING m_facing_direction;
	//Stores the current LevelMap pointer
	LevelMap* m_current_level_map;
public:
	Character(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	void SetPosition(Vector2D new_position);
	Vector2D GetPosition();
	//Functions for getting collision size
	float GetCollisionRadius();
	//Created as an inline function as it is only returning a struct in the header
	Rect2D GetCollisionBox()
	{
		return Rect2D(m_position.x, m_position.y, m_texture->GetWidth(), m_texture->GetHeight());
	}

	bool IsJumping() { return m_jumping; }

	void CancelJump()
	{
		m_jumping = false;
		m_jump_force = 0.0f;
	}
};

#endif //_CHARACTER_H