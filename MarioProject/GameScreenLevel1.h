#pragma once
#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H

//File references
#include "GameScreen.h" //includes SDL.h as it is included in GameScreen.h
#include "Commons.h"

class Texture2D; //Forward declaration of class

class GameScreenLevel1 : GameScreen // Inherits from class type GameScreen
{
	private:
		Texture2D* m_background_texture; //Reference to Texture2D, can be used because of forward declaration
		bool SetUpLevel(); //private function only used by this class
	public:
		GameScreenLevel1(SDL_Renderer* renderer);
		~GameScreenLevel1();

		void Render() override; //override is optional but good practice to understand the code better
		void Update(float deltaTime, SDL_Event e) override;
};

#endif //_GAMESCREENLEVEL1_H