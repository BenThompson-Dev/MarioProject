#include <iostream>
#include <string>
//SDL Headers
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
//Header files
#include "constants.h"

//Globals
SDL_Window* g_window = nullptr; //Pointer
SDL_Renderer* g_renderer = nullptr; //Renderer pointer
SDL_Texture* g_texture = nullptr;

//Function prototypes
bool InitSDL();
void CloseSDL();
bool Update();
//Tutorial 4
void Render();
SDL_Texture* LoadTextureFromFile(std::string path);
void FreeTexture();

SDL_RendererFlip imageFlipped = SDL_FLIP_NONE;
double imageAngle = 0;

int main(int argc, char* args[])
{
	if (InitSDL())
	{
		//Flag to check if we wish to quit
		bool quit = false;
		//Game loop
		while (!quit)
		{
			Render();
			quit = Update();
		}
	}

	CloseSDL();

	return 0;
}

bool Update()
{
	//Event handler, local and will go out of scope at end of Update function
	SDL_Event e;

	//Get Events
	//Event variable e passed by reference, so it can be changed in function
	SDL_PollEvent(&e);

	//Handle the events
	switch (e.type)
	{
		//Click the 'X' to quit
		//SDL_QUIT is the variable type returned when 'X' is pressed
		case SDL_QUIT:
			return true;
			break;
		//Checks if key has been pressed down
		case SDL_KEYUP:
			//Nested switch statement checks which key has been pressed down
			switch (e.key.keysym.sym)
			{
				//If key is Q
				case SDLK_q:
					return true;
					break;
				case SDLK_a:
					if (imageFlipped == SDL_FLIP_NONE)
					{
						imageFlipped = SDL_FLIP_HORIZONTAL;
					}
					else
					{
						imageFlipped = SDL_FLIP_NONE;
					}
					break;
				case SDLK_s:
					imageAngle += 10;
					break;
			}
		//Checks if a mouse button has been pressed down
		case SDL_MOUSEBUTTONDOWN:
			/*Nested switch checks for which mouse button has been pressed
			First .button is event data, second .button is button index*/
			switch (e.button.button)
			{
				//If right mouse button has been pressed down
				case SDL_BUTTON_RIGHT:
					return true;
					break;
			}
	}

	return false;
}

bool InitSDL()
{
	//Setup SDL
	//Initialises SDL using video subsystem
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	}
	else
	{
		//Setup passed, window can be created
		g_window = SDL_CreateWindow("Games Engine Creation", //Window name
			SDL_WINDOWPOS_UNDEFINED, //Screen position X
			SDL_WINDOWPOS_UNDEFINED, //Screen position Y
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
		//Checks if the window got created, pointer will return null
		if (g_window == nullptr)
		{
			//Window failed
			std::cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}
	}
	//Renderer Setup
	g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
	/*Parameters: window associated with renderer, index initilising with flags,
	combination of SDL_RenderFlags*/

	if (g_renderer != nullptr) //Checks to make sure renderer exists
	{
		int imageFlags = IMG_INIT_PNG; //Initilisation PNG loading
		if (!(IMG_Init(imageFlags) & imageFlags)) //Checks if IMG_INIT_PNG is not returned
		{
			std::cout << "SDL_Image could not initialise. Error: " << IMG_GetError();
			return false;
		}
		//Loads the background texture
		g_texture = LoadTextureFromFile("Images/test.bmp");
		if (g_texture == nullptr) //Error checking
		{
			return false;
		}
	}
	else
	{
		std::cout << "Renderer could not initialise. Error: " << SDL_GetError();
		return false;
	}
}

void CloseSDL()
{
	//Release the window, frees memory
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	//Quit SDL systems
	IMG_Quit();
	SDL_Quit();

	//Clear the texture
	FreeTexture();
	//Release the renderer
	SDL_DestroyRenderer(g_renderer);
	g_renderer = nullptr;
	/*The pointers are reassigned to nullptr after being deleted
	This prevents double delete errors or should a condition
	later in the program require3 something to be null won't trigger
	It is known as a dangling pointer, if not reassigned it will hold an
	invalid address and crash the program*/
}

void Render()
{
	//Clear the screen
	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF); //Sets colour for renderer
	SDL_RenderClear(g_renderer); //Clears window

	//Set where to render the texture
	SDL_Rect renderLocation = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT }; //SDL_Rect holds locational data

	//Render to the screen
	SDL_RenderCopyEx(g_renderer, g_texture, NULL, &renderLocation, imageAngle, NULL, imageFlipped);
	/*SDL_RenderCopyEx allows you to set different flags. Parameters are:
	the renderer, the texture, a source rect, a destination rect, an angle,
	an SDL_Point for the centre of the texture and an SDL_RendererFlip flag (image flip)*/

	//Update the screen
	SDL_RenderPresent(g_renderer);
}

SDL_Texture* LoadTextureFromFile(std::string path)
{
	//Remove memory used for a previous texture
	FreeTexture();
	
	SDL_Texture* p_texture = nullptr; //SDL_Texture pointer
	//Load the image
	SDL_Surface* p_surface = IMG_Load(path.c_str()); /*Loads image
	path to image file is inputted through char array, c_str() converts from string*/
	if (p_surface != nullptr)
	{
		//If passed, surface is correctly set up
		//Create the texture from the pixels on the surface
		p_texture = SDL_CreateTextureFromSurface(g_renderer, p_surface);
		if (p_texture == nullptr) //If texture isnt created properly
		{
			std::cout << "Unable to create texture from surface. Error: " << SDL_GetError();
		}
		//Remove the loaded surface now that we have a texture
		SDL_FreeSurface(p_surface); //If the texture is created successfully, we can delete the surface
	}
	else
	{
		std::cout << "Unable to create texture from surface. Error: " << IMG_GetError();
	}
	//Texture type must be returned
	return p_texture; //Returns the loaded texture
}

void FreeTexture()
{
	//Check if texture exists before removing it
	if (g_texture != nullptr)
	{
		SDL_DestroyTexture(g_texture);
		g_texture = nullptr;
	}
}