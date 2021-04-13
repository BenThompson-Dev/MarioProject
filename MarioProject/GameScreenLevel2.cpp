#include "GameScreenLevel2.h"
#include <iostream>
#include "Texture2D.h"
#include "AudioManager.h"
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterCoin.h"
#include "LevelMapLevel2.h"

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
	delete m_audio_manager;
	m_audio_manager = nullptr;

	m_coins.clear();
}

void GameScreenLevel2::Render(float deltaTime)
{
	//Draw coins
	//Drawn before background so they can 'come out' of the pipes
	for (int i = 0; i < m_coins.size(); i++)
	{
		m_coins[i]->Render(deltaTime);
	}

	//Draw the background
	m_background_texture->Render(Vector2D(0, 0), SDL_FLIP_NONE); //Calls the Texture2D pointer's Render function
	//m_background_texture is set to be a reference to the Texture2D class

	mario->Render();
}

void GameScreenLevel2::Update(float deltaTime, SDL_Event e)
{
	//Update characters
	mario->Update(deltaTime, e);

	UpdateEnemies(deltaTime, e);
	UpdateCoins(deltaTime, e);
}

bool GameScreenLevel2::SetUpLevel()
{
	//Creates new audio manager for level, loads and begins to play music
	m_audio_manager = new AudioManager("Audio/MUS_Mario.mp3");

	//Load texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/BackgroundMB.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}

	SetLevelMap();

	//Set up mario character
	mario = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 330), m_level_map, m_audio_manager);
}

void GameScreenLevel2::SetLevelMap()
{
	//Level initialisation
	int map[LEVEL2_MAP_HEIGHT][LEVEL2_MAP_WIDTH] = { {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
										{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0 },
										{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
										{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0 },
										{1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1 },
										{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
										{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1 } };

	//Clear any old maps
	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}
	//Sets the new map
	m_level_map = new LevelMapLevel2(map);
}

void GameScreenLevel2::UpdateEnemies(float deltaTime, SDL_Event e)
{

}

void GameScreenLevel2::UpdateCoins(float deltaTime, SDL_Event e)
{

}

void GameScreenLevel2::CreateCoin(Vector2D position, FACING direction, float speed)
{

}