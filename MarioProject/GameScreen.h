#pragma once
//macro
#ifndef _GAMESCREEN_H
#define _GAMESCREEN_H

#include <SDL.h>

class GameScreen
{
	protected:
		SDL_Renderer* m_renderer; //Creates renderer ref

	public:
		GameScreen(SDL_Renderer* renderer);
		~GameScreen();

		virtual void Render(float deltaTime);
		virtual void Update(float deltaTime, SDL_Event e);
};

#endif //_GAMESCREEN_H