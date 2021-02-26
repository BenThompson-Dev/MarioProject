#include <iostream>
#include <string>

#include "POWBlock.h"
#include "Texture2D.h"
#include "LevelMap.h"
#include "constants.h"

POWBlock::POWBlock(SDL_Renderer* renderer, LevelMap* map)
{
	std::string imagePath = "Images/PowBlock.png";
	m_texture = new Texture2D(renderer);

	if (!m_texture->LoadFromFile(imagePath.c_str()))
	{
		std::cout << "Failed to load texture." << std::endl;
		return;
	}

	m_level_map = map;
	m_single_sprite_w = m_texture->GetWidth() / 3; //There are three images in the spritesheet in a row
	m_single_sprite_h = m_texture->GetHeight();
	m_num_hits_left = 3;
	m_position = Vector2D((SCREEN_WIDTH * 0.5f) - m_single_sprite_w * 0.5f, 260);
}

POWBlock::~POWBlock()
{
	/*m_renderer and m_level_map are being used by other classes, so are
	not deleted; if they were the program would crash*/
	m_renderer = nullptr;
	m_level_map = nullptr;
	delete m_texture;
	m_texture = nullptr;
}

void POWBlock::Render()
{
	if (m_num_hits_left > 0)
	{
		//Get the portion of the sheet we want to draw
		int left = m_single_sprite_w * (m_num_hits_left - 1);
		//							 xPos, yPos, single sprite width, single sprite height
		SDL_Rect portion_of_sprite = { left, 0, m_single_sprite_w, m_single_sprite_h };
		//Determine where to draw it
		SDL_Rect dest_rect = { static_cast<int>(m_position.x), static_cast<int>(m_position.y), m_single_sprite_w, m_single_sprite_h };
		//Draw the sprite
		m_texture->Render(portion_of_sprite, dest_rect, SDL_FLIP_NONE);
	}
}

void POWBlock::TakeHit()
{
	m_num_hits_left--;

	if (m_num_hits_left <= 0)
	{
		m_num_hits_left = 0;
		m_level_map->ChangeTileAt(8, 7, 0);
		m_level_map->ChangeTileAt(8, 8, 0);
	}
}