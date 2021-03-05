#include "TextCharacter.h"
#include "Texture2D.h"
#include "constants.h"

#include <iostream>

TextCharacter::TextCharacter(SDL_Renderer* renderer, std::string filePath, Vector2D position)
{
	m_renderer = renderer;
	m_image = filePath;
	m_position = position;

	m_texture = new Texture2D(m_renderer);
	if (!m_texture->LoadFromFile(m_image))
	{
		std::cout << "Failed to load texture!" << std::endl;
	}

	m_single_sprite_w = FONT_WIDTH;
	m_single_sprite_h = FONT_HEIGHT;
}

TextCharacter::~TextCharacter()
{
	m_renderer = nullptr;
}

void TextCharacter::Render(int displayChar)
{
	SDL_Rect portion_of_sprite = { (m_single_sprite_w * displayChar), 0, m_single_sprite_w, m_single_sprite_h };
	SDL_Rect destRect = { (int)(m_position.x), (int)(m_position.y), m_single_sprite_w, m_single_sprite_h };
	m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_NONE);
}

void TextCharacter::Render(char displayChar)
{

}