#include "GameScreenLevel2.h"
#include "Texture2D.h"
#include "LevelMap.h"
#include <iostream>

GameScreenLevel2::GameScreenLevel2(SDL_Renderer* renderer) : GameScreen(renderer)
{
	m_level_map = nullptr;

	SetUpLevel();
}

GameScreenLevel2::~GameScreenLevel2()
{
	delete m_background_texture;
	m_background_texture = nullptr;
	delete mario;
	mario = nullptr;
}

void GameScreenLevel2::Render(float deltaTime)
{
	//Draw background
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE);
}

void GameScreenLevel2::Update(float deltaTime, SDL_Event e)
{

}

bool GameScreenLevel2::SetUpLevel()
{
	//Creates new audio manager for level, loads and begins to play music
	m_audio_manager = new AudioManager("Audio/MUS_Mario.mp3");

	SetLevelMap();

	//Load background texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/BackgroundSMB.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}

	mario = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 330), m_level_map, m_audio_manager);
}

void GameScreenLevel2::SetLevelMap()
{
	//Clear any old maps
	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}
	//Sets the new map
	m_level_map = new LevelMap(2);
}