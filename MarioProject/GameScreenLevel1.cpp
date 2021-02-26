#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include "Collisions.h"
#include "POWBlock.h"
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
	delete m_pow_block;
	m_pow_block = nullptr;
}

void GameScreenLevel1::Render()
{
	//Draw the background
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE); //Calls the Texture2D pointer's Render function
	//m_background_texture is set to be a reference to the Texture2D class

	mario->Render();
	luigi->Render();
	m_pow_block->Render();
}
void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	/*
	 *	Do the screen shake if required
	 */
	if (m_screenshake)
	{
		m_shake_time -= deltaTime;
		m_wobble++;
		m_background_yPos = sin(m_wobble);
		m_background_yPos *= 3.0f;
		//End shake after duration
		if (m_shake_time <= 0.0f)
		{
			m_screenshake = false;
			m_background_yPos = 0.0f;
		}
	}

	//Update characters
	mario->Update(deltaTime, e);
	luigi->Update(deltaTime, e);

	UpdatePOWBlock();

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

void GameScreenLevel1::UpdatePOWBlock()
{
	if (Collisions::Instance()->Box(mario->GetCollisionBox(), m_pow_block->GetCollisionBox()))
	{
		if (m_pow_block->IsAvailable() > 0)
		{
			//Collided while jumping
			if (mario->IsJumping())
			{
				DoScreenShake();
				m_pow_block->TakeHit();
				mario->CancelJump();
			}
		}
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

	//Set up pow block
	m_pow_block = new POWBlock(m_renderer, m_level_map);
	m_screenshake = false;
	m_background_yPos = 0.0f;
}

void GameScreenLevel1::SetLevelMap()
{
	//Level initialisation
	int map[MAP_HEIGHT][MAP_WIDTH] = {  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
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

void GameScreenLevel1::DoScreenShake()
{
	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;
}