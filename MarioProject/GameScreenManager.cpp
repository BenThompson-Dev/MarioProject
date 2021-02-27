#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreenLevel1.h"

GameScreenManager::GameScreenManager(SDL_Renderer* renderer, SCREENS startScreen)
{
	m_renderer = renderer;
	m_current_screen = nullptr; //Sets the current screen to be a null pointer

	ChangeScreen(startScreen);
}

GameScreenManager::~GameScreenManager()
{
	m_renderer = nullptr;
	delete m_current_screen;
	m_current_screen = nullptr;
}

void GameScreenManager::Render(float deltaTime)
{
	m_current_screen->Render(deltaTime);
}

void GameScreenManager::Update(float deltaTime, SDL_Event e)
{
	m_current_screen->Update(deltaTime, e);
}

void GameScreenManager::ChangeScreen(SCREENS new_screen)
{
	//Clear up the old screen
	if (m_current_screen != nullptr)
	{
		delete m_current_screen;
	}

	GameScreenLevel1* tempScreen; //Sets up reference before switch

	switch (new_screen)
	{
		case SCREEN_LEVEL1:
			tempScreen = new GameScreenLevel1(m_renderer);
			m_current_screen = (GameScreen*)tempScreen;
			tempScreen = nullptr;
		default:; //If default, does nothing
	}
}