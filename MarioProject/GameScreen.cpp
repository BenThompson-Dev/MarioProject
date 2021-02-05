#include "GameScreen.h"
#include <SDL_image.h>
#include <iostream>

GameScreen::GameScreen(SDL_Renderer* renderer)
{
	m_renderer = renderer;
}

GameScreen::~GameScreen()
{
	m_renderer = nullptr;
}

//Virtual classes get overriden in deriving classes
void GameScreen::Render(){}

void GameScreen::Update(float deltaTime, SDL_Event e){}