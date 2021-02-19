#include "Character.h"
#include "Texture2D.h"
#include "constants.h"

Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, LevelMap* map)
{
	m_renderer = renderer;
	m_position = start_position;
	m_image = imagePath;
	m_facing_direction = FACING_RIGHT; //Changes mario's direction to facing right (default image direction)
	//Load texture
	m_texture = new Texture2D(m_renderer);
	if (!m_texture->LoadFromFile(imagePath))
	{
		std::cout << "Failed to load background texture!" << std::endl;
	}
	//No movement at the start of the game
	m_moving_left = false;
	m_moving_right = false;

	//Sets radius of collision
	m_collision_radius = CHAR_COLLISION_RADIUS;

	m_current_level_map = map;
}

Character::~Character()
{
	m_renderer = nullptr;
}

void Character::Render()
{
	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(m_position, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(m_position, SDL_FLIP_HORIZONTAL);
	}
}

void Character::Update(float deltaTime, SDL_Event e)
{
	if (m_jumping)
	{
		m_position.y -= deltaTime * m_jump_force;
		//Reduces the jump force
		m_jump_force -= deltaTime * JUMP_FORCE_DECREMENT;
		if (m_jump_force <= 0.0f)
			m_jumping = false;
	}

	//Collision position variables
	int centralX_position = (int)(m_position.x + (m_texture->GetWidth() * 0.5)) / TILE_WIDTH;
	int foot_position = (int)(m_position.y + m_texture->GetHeight()) / TILE_HEIGHT;

	//Check if gravity should be applied
	if (m_current_level_map->GetTileAt(foot_position, centralX_position) == 0)
	{
		AddGravity(deltaTime);
	}
	else
	{
		//Collided with ground, so player can jump again
		m_can_jump = true;
	}

	if (m_moving_left)
	{
		MoveLeft(deltaTime);
	}
	else if (m_moving_right)
	{
		MoveRight(deltaTime);
	}
}

void Character::SetPosition(Vector2D new_position)
{
	m_position = new_position;
}

Vector2D Character::GetPosition()
{
	return m_position;
}

void Character::MoveLeft(float deltaTime)
{
	m_position.x -= deltaTime * MOVEMENT_SPEED;
	if (m_image == "Images/Mario.png")
		m_facing_direction = FACING_LEFT;
	else
		m_facing_direction = FACING_RIGHT;
}

void Character::MoveRight(float deltaTime)
{
	m_position.x += deltaTime * MOVEMENT_SPEED;
	if (m_image == "Images/Mario.png")
		m_facing_direction = FACING_RIGHT;
	else
		m_facing_direction = FACING_LEFT;
}

void Character::AddGravity(float deltaTime)
{
	//Mario sprite height
	if (m_position.y + CHARACTER_SIZE <= SCREEN_HEIGHT)
	{
		m_position.y += deltaTime * GRAVITY;
	}
	else
	{
		m_can_jump = true;
		m_jumping = false;
	}
}

void Character::Jump(float deltaTime)
{
	m_jump_force = INITIAL_JUMP_FORCE;
	m_jumping = true;
	m_can_jump = false;
}

float Character::GetCollisionRadius()
{
	return m_collision_radius;
}