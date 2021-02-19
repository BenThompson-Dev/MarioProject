#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include "Collisions.h"
#include <iostream>

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer) //Inherits from GameScreen
{
	m_level_map = nullptr;
	SetUpLevel();
}

GameScreenLevel1::~GameScreenLevel1()
{
	delete m_background_texture;
	m_background_texture = nullptr;
	delete mario;
	mario = nullptr;
	delete luigi;
	luigi = nullptr;
}

void GameScreenLevel1::Render()
{
	//Draw the background
	m_background_texture->Render(Vector2D(), SDL_FLIP_NONE); //Calls the Texture2D pointer's Render function
	//m_background_texture is set to be a reference to the Texture2D class

	mario->Render();
	luigi->Render();
}
void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	//Update characters
	mario->Update(deltaTime, e);
	luigi->Update(deltaTime, e);
	//Checks for the different collision types
	if (Collisions::Instance()->Circle(mario, luigi))
	{
		std::cout << "Circle hit!" << std::endl;
	}
	if (Collisions::Instance()->Box(mario->GetCollisionBox(), luigi->GetCollisionBox()))
	{
		std::cout << "Box hit!" << std::endl;
	}
}

bool GameScreenLevel1::SetUpLevel()
{
	//Load texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/BackgroundMBChanged.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}

	SetLevelMap();

	//Set up mario character
	mario = new CharacterMario(m_renderer, "Images/Mario.png", Vector2D(64, 330), m_level_map);
	//Set up luigi character
	luigi = new CharacterLuigi(m_renderer, "Images/Luigi.png", Vector2D(406, 330), m_level_map);
}

void GameScreenLevel1::SetLevelMap()
{
	//Level initialisation
	int map[MAP_HEIGHT][MAP_WIDTH] = { { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
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
	m_level_map = new LevelMap(map);
}