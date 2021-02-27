#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include "Collisions.h"
#include "POWBlock.h"
#include <vector>

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

	m_enemies.clear();
}

void GameScreenLevel1::Render()
{
	//Draws black background image first
	m_background_colour->Render(Vector2D(0, 0), SDL_FLIP_NONE);
	//Doesn't use m_background_yPos as it is just the background colour, it doesn't need to move with the screen shake

	//Draw the enemies
	//Drawn before background so they can 'come out' of the pipes
	for (int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->Render();
	}

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

	//Check to see if new enemies need to be respawned
	if (enemyRespawnCounter <= 0)
	{
		CreateKoopa(Vector2D(0, 32), FACING_RIGHT, KOOPA_SPEED);
		CreateKoopa(Vector2D(SCREEN_WIDTH-50, 32), FACING_LEFT, KOOPA_SPEED);
		//Screen Size - buffer value, stops them from falling onto the below platform

		enemyRespawnCounter = ENEMY_RESPAWN_TIME;
	}
	else
	{
		enemyRespawnCounter -= deltaTime;
	}

	//Update characters
	mario->Update(deltaTime, e);
	luigi->Update(deltaTime, e);

	UpdatePOWBlock();
	UpdateEnemies(deltaTime, e);

	/*Checks for the different collision types
	if (Collisions::Instance()->Circle(mario, luigi))
	{
		std::cout << "Circle hit!" << std::endl;
	}
	if (Collisions::Instance()->Box(mario->GetCollisionBox(), luigi->GetCollisionBox()))
	{
		std::cout << "Box hit!" << std::endl;
	}*/
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
	//Alternate check to see if Luigi is colliding with the POW Block
	if (Collisions::Instance()->Box(luigi->GetCollisionBox(), m_pow_block->GetCollisionBox()))
	{
		if (m_pow_block->IsAvailable() > 0)
		{
			if (luigi->IsJumping())
			{
				DoScreenShake();
				m_pow_block->TakeHit();
				luigi->CancelJump();
			}
		}
	}
}

bool GameScreenLevel1::SetUpLevel()
{
	m_background_colour = new Texture2D(m_renderer);
	if (!m_background_colour->LoadFromFile("Images/Black.png"))
	{
		std::cout << "Failed to load background colour texture!" << std::endl;
		return false;
	}

	//Load texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/BackgroundMB.png"))
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

	for (unsigned int i = 0; i < m_enemies.size(); i++)
	{
		m_enemies[i]->TakeDamage();
	}
}

void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	std::cout << m_enemies.size() << std::endl;

	if (!m_enemies.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < m_enemies.size(); i++)
		{
			//Check if the enemy is on the bottom row of tiles
			if (m_enemies[i]->GetPosition().y > 300.0f)
			{
				//Is the enemy off screen to the left / right?
				if (m_enemies[i]->GetPosition().x < (float)(-m_enemies[i]->GetCollisionBox().width * 0.5f) ||
					m_enemies[i]->GetPosition().x > SCREEN_WIDTH - (float)(m_enemies[i]->GetCollisionBox().width * 0.55f))
				{
					m_enemies[i]->SetAlive(false);
				}
			}
			//Now do the update
			m_enemies[i]->Update(deltaTime, e);

			//Check to see if enemy collides with player
			if ((m_enemies[i]->GetPosition().y > 300.0f || m_enemies[i]->GetPosition().y <= 64.0f) &&
				(m_enemies[i]->GetPosition().x < 64.0f || m_enemies[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				//Ignore collisions if behind pipe
			}
			else
			{
				if (Collisions::Instance()->Circle(m_enemies[i], mario))
				{
					if (m_enemies[i]->GetInjured())
					{
						m_enemies[i]->SetAlive(false);
					}
					else
					{
						//Kill mario
					}
				}
				else if (Collisions::Instance()->Circle(m_enemies[i], luigi))
				{
					if (m_enemies[i]->GetInjured())
					{
						m_enemies[i]->SetAlive(false);
					}
					else
					{
						//Kill luigi
					}
				}
			}
			
			//If the enemy is no longer alive then schedule it for deletion
			if (!m_enemies[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}
		}

		//Remove dead enemies -1 each update
		if (enemyIndexToDelete != -1)
		{
			m_enemies.erase(m_enemies.begin() + enemyIndexToDelete);
		}
	}
}

void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	koopa = new CharacterKoopa(m_renderer, "Images/Koopa.png", m_level_map, Vector2D(position.x, position.y), direction, speed);
	m_enemies.push_back(koopa);
}