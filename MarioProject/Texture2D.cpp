#include "Texture2D.h"
#include <SDL_image.h>
#include <iostream>

//Constructor
Texture2D::Texture2D(SDL_Renderer* renderer)
{
	m_renderer = renderer;
}
//Destructor
Texture2D::~Texture2D()
{
	//Free up memory
	Free();

	m_renderer = nullptr;
}

bool Texture2D::LoadFromFile(std::string path)
{
	//Remove memory used for a previous texture
	Free();

	//Load the image
	SDL_Surface* p_surface = IMG_Load(path.c_str()); /*Loads image
	path to image file is inputted through char array, c_str() converts from string*/
	if (p_surface != nullptr)
	{
		//If passed, surface is correctly set up
		SDL_SetColorKey(p_surface, SDL_TRUE, SDL_MapRGB(p_surface->format, 0, 0XFF, 0XFF));

		//Create the texture from the pixels on the surface
		m_texture = SDL_CreateTextureFromSurface(m_renderer, p_surface);
		if (m_texture == nullptr) //If texture isnt created properly
		{
			std::cout << "Unable to create texture from surface. Error: " << SDL_GetError();
		}
		else
		{
			m_width = p_surface->w;
			m_height = p_surface->h;
		}
		//Remove the loaded surface now that we have a texture
		SDL_FreeSurface(p_surface); //If the texture is created successfully, we can delete the surface
	}
	else
	{
		std::cout << "Unable to create texture from surface. Error: " << IMG_GetError();
	}
	//Return whether the process was successful
	return m_texture != nullptr;
}

void Texture2D::Free()
{
	//Checks if texture exists before removing it
	if (m_texture != nullptr)
	{
		SDL_DestroyTexture(m_texture);
		m_texture = nullptr;
		m_width = 0;
		m_height = 0;
	}
}
void Texture2D::Render(Vector2D new_position, SDL_RendererFlip flip, double angle)
{
	//Set where to render the texture
	SDL_Rect renderLocation = { 0,0,m_width,m_height }; //SDL_Rect holds locational data

	//Render to the screen
	SDL_RenderCopyEx(m_renderer, m_texture, nullptr, &renderLocation, 0, nullptr, SDL_FLIP_NONE);
	/*SDL_RenderCopyEx allows you to set different flags. Parameters are:
	the renderer, the texture, a source rect, a destination rect, an angle,
	an SDL_Point for the centre of the texture and an SDL_RendererFlip flag (image flip)*/
}