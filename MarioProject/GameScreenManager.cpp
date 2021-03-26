#include "GameScreenManager.h"
#include "GameScreen.h"
#include "GameScreenLevel1.h"
#include "GameScreenLevel2.h"

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

	GameScreenLevel1* tempScreenLevel1; //Sets up reference before switch
	GameScreenLevel2* tempScreenLevel2;

	switch (new_screen)
	{
		case SCREEN_LEVEL1:
			tempScreenLevel1 = new GameScreenLevel1(m_renderer);
			m_current_screen = (GameScreen*)tempScreenLevel1;
			tempScreenLevel1 = nullptr;
		case SCREEN_LEVEL2:
			tempScreenLevel2 = new GameScreenLevel2(m_renderer);
			m_current_screen = (GameScreen*)tempScreenLevel2;
			tempScreenLevel2 = nullptr;
		default:; //If default, does nothing
	}
}