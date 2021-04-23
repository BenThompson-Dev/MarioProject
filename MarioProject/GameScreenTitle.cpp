#include "GameScreenTitle.h"
#include "Texture2D.h"

#include <iostream>

GameScreenTitle::GameScreenTitle(SDL_Renderer* m_renderer) : GameScreen(m_renderer)
{
	SetUpLevel();
}

GameScreenTitle::~GameScreenTitle()
{
	delete m_background_colour;
	m_background_colour = nullptr;
	delete character;
	character = nullptr;

	m_characters.clear();
}

void GameScreenTitle::Update(float deltaTime, SDL_Event e)
{
	switch (e.type)
	{
	case SDL_KEYDOWN:
		switch (e.key.keysym.sym)
		{
		case SDLK_q:

			break;
		}
		break;
	}
}

void GameScreenTitle::Render(float deltaTime)
{
	//Draws black background image first
	m_background_colour->Render(Vector2D(0, 0), SDL_FLIP_NONE);

	for (unsigned int i = 0; i < m_characters.size(); i++) //Loops through each screen character
	{
		m_characters[i]->Render(titleText[i]); //Renders text to screen
	}
}

void GameScreenTitle::SetUpLevel()
{
	//Text setup
	titleText = "Mario Bros";
	SetUpText({ 100, 100 }); //Sets up title screen text

	m_background_colour = new Texture2D(m_renderer);
	if (!m_background_colour->LoadFromFile("Images/Black.png"))
	{
		std::cout << "Failed to load background colour texture!" << std::endl;
	}
}

void GameScreenTitle::SetUpText(Vector2D position)
{
	for (int i = 0; i < titleText.length(); i++)
	{
		character = new TextCharacter(m_renderer, "Images/FontAlphabet.png", position); //Creates new character
		m_characters.push_back(character); //Pushes character into array
	}
}