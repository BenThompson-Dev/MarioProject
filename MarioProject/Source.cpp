#include <iostream>
#include <string>
//SDL Headers
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
//Header files
#include "constants.h"
#include "Texture2D.h"
#include "Commons.h"
#include "GameScreenManager.h"

//Globals
SDL_Window* g_window = nullptr; //Pointer
SDL_Renderer* g_renderer = nullptr; //Renderer pointer
GameScreenManager* game_screen_manager; //GameScreenManager pointer

Uint32 g_old_time; //Delta time reference

//Function prototypes
bool InitSDL();
void CloseSDL();
bool Update();
//Tutorial 4
void Render();
//SDL_Texture* LoadTextureFromFile(std::string path);
//void FreeTexture();

int main(int argc, char* args[])
{
	if (InitSDL())
	{
		game_screen_manager = new GameScreenManager(g_renderer, SCREEN_LEVEL1);
		//Sets the time
		g_old_time = SDL_GetTicks();

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
	Uint32 new_time = SDL_GetTicks();

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
	//Runs game screen manager update
	game_screen_manager->Update((float)(new_time - g_old_time) / 1000.0f, e);

	//Changes time
	g_old_time = new_time;

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

	//Release the renderer
	SDL_DestroyRenderer(g_renderer);
	g_renderer = nullptr;
	/*The pointers are reassigned to nullptr after being deleted
	This prevents double delete errors or should a condition
	later in the program require3 something to be null won't trigger
	It is known as a dangling pointer, if not reassigned it will hold an
	invalid address and crash the program*/

	//Destroys the game screen manager
	delete game_screen_manager;
	game_screen_manager = nullptr;
}

void Render()
{
	//Clear the screen
	SDL_SetRenderDrawColor(g_renderer, 0xFF, 0xFF, 0xFF, 0xFF); //Sets colour for renderer
	SDL_RenderClear(g_renderer); //Clears window
	
	game_screen_manager->Render();

	//Update the screen
	SDL_RenderPresent(g_renderer);
}