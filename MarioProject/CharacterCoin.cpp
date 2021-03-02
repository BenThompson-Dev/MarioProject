#include "CharacterCoin.h"

CharacterCoin::CharacterCoin(SDL_Renderer* renderer, std::string imagePath, LevelMap* map, Vector2D start_position, FACING start_facing, float movement_speed) : Character(renderer, imagePath, start_position, map)
{
	m_facing_direction = start_facing;
	m_movement_speed = movement_speed;
	m_position = start_position;

	m_single_sprite_w = m_texture->GetWidth() / 3;
	m_single_sprite_h = m_texture->GetHeight();

	m_frame_delay = ANIMATION_DELAY;
}

CharacterCoin::~CharacterCoin()
{

}

void CharacterCoin::Jump()
{
	if (!m_jumping)
	{
		m_jump_force = INITIAL_JUMP_FORCE_SMALL;
		m_jumping = true;
		m_can_jump = false;
	}
}

void CharacterCoin::Render(float deltaTime)
{
	m_frame_delay -= deltaTime;
	if (m_frame_delay <= 0.0f)
	{
		//Reset frame delay count
		m_frame_delay = ANIMATION_DELAY;
		//move the frame over
		m_current_frame++;
		//Loop frame around if it goes beyond the number of frames
		if (m_current_frame > 2)
		{
			m_current_frame = 0;
		}
	}
	
	//Get portion of sprite sheet
	//							  xPos, yPos,  sprite width,    sprite height
	SDL_Rect portion_of_sprite = { m_single_sprite_w * m_current_frame, 0, m_single_sprite_w, m_single_sprite_h };
	//Determine where to draw
	SDL_Rect destRect = { (int)(m_position.x), (int)(m_position.y), m_single_sprite_w, m_single_sprite_h };
	//The n draw it facing correct direction
	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_HORIZONTAL);
	}
}

void CharacterCoin::Update(float deltaTime, SDL_Event e)
{
	Character::Update(deltaTime, e);

	//Checks to see if coin is at screen boundaries
	if (m_position.x <= 0 || m_position.x >= SCREEN_WIDTH - 32)
	{
		//Checks to make sure they aren't on the lowest row
		if (m_position.y < 350)
		{
			//If true, have coin face opposite direction
			if (m_facing_direction == FACING_LEFT)
				m_facing_direction = FACING_RIGHT;
			else
				m_facing_direction = FACING_LEFT;
		}
	}

	if (m_facing_direction == FACING_LEFT)
	{
		m_moving_left = true;
		m_moving_right = false;
	}
	else if (m_facing_direction == FACING_RIGHT)
	{
		m_moving_left = false;
		m_moving_right = true;
	}
}