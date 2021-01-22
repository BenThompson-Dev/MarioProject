#include <iostream>
//SDL Headers
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
//Header files
#include "constants.h"

//Globals
SDL_Window* g_window = nullptr; //Pointer

//Function prototypes
bool InitSDL();
void CloseSDL();
bool Update();

int main(int argc, char* args[])
{
	if (InitSDL())
	{
		//Flag to check if we wish to quit
		bool quit = false;
		//Game loop
		while (!quit)
		{
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
}

void CloseSDL()
{
	//Release the window, frees memory
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	//Quit SDL systems
	IMG_Quit();
	SDL_Quit();
}