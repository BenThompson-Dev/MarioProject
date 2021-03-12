#pragma once
#ifndef _PLAYERSCORE_H
#define _PLAYERSCORE_H

#include <SDL.h>
#include <vector>
#include "Commons.h"

class TextCharacter;

class PlayerScore
{
private:
	Vector2D m_position;
	TextCharacter* character;
	std::vector<TextCharacter*> m_numbers; //Vector holds each number in the score display

	int score = 0;
	int separatedScore[3];

	void Update();
public:
	PlayerScore(SDL_Renderer* renderer);
	~PlayerScore();

	void Render();
	int GetScore() { return score; }
	void IncrementScore(int increment);
};

#endif //_PLAYERSCORE_H