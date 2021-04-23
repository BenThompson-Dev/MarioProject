#pragma once
#ifndef _TEXTCHARACTER_H
#define _TEXTCHARACTER_H

#include <SDL.h>
#include <string>
#include "Commons.h"

class Texture2D;

class TextCharacter
{
private:
	SDL_Renderer* m_renderer;
	Vector2D m_position;
	std::string m_image;

	int displayPosition; //Holds position to render from in character image

	Texture2D* m_texture;

	int m_single_sprite_w;
	int m_single_sprite_h;
public:
	TextCharacter(SDL_Renderer* renderer, std::string filePath, Vector2D position);
	~TextCharacter();

	//Multiple versions of the function depending whether letter or number passed through
	void Render(int displayChar); //Called by PlayerScore class
	void Render(char displayChar);
};

#endif //_TEXTCHARACTER_H