#pragma once
#ifndef _GAMESCREENTITLE_H
#define _GAMESCREENTITLE_H

#include "GameScreen.h"
#include "Commons.h"
#include "TextCharacter.h"
#include <string>
#include <vector>

class GameScreenTitle : public GameScreen
{
private:
	void SetUpLevel();
	void SetUpText(Vector2D position);

	std::vector<TextCharacter*> m_characters; //Holds all characters on title screen*
	TextCharacter* character;

	Texture2D* m_background_colour;

	std::string titleText;
public:
	GameScreenTitle(SDL_Renderer* m_renderer);
	~GameScreenTitle();

	void Update(float deltaTime, SDL_Event e) override;
	void Render(float deltaTime) override;
};

#endif //_GAMESCREENTITLE_H