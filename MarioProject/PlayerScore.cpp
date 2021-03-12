#include "PlayerScore.h"
#include "TextCharacter.h"
#include "constants.h"

#include <math.h>

PlayerScore::PlayerScore(SDL_Renderer* renderer)
{
	//Positioned to be the top-left of the rightmost number
	m_position = Vector2D(260.0f, 16.0f);

	//Initialises numbers array
	character1 = new TextCharacter(renderer, "Images/FontNumbers.png", Vector2D((m_position.x), m_position.y));
	m_numbers.push_back(character1);
	character2 = new TextCharacter(renderer, "Images/FontNumbers.png", Vector2D((m_position.x - (FONT_WIDTH * 1)), m_position.y));
	m_numbers.push_back(character2);
	character3 = new TextCharacter(renderer, "Images/FontNumbers.png", Vector2D((m_position.x - (FONT_WIDTH * 2)), m_position.y));
	m_numbers.push_back(character3);

	/*for (int i = 0; i < SCORE_CHAR_AMOUNT; i++)
	{
		//																(top-left of final digit - width of digits * position in number)
		character = new TextCharacter(renderer, "Images/FontNumbers.png", Vector2D((m_position.x - (FONT_WIDTH * i)), m_position.y));
	}
	m_numbers.push_back(character);*/
} 

PlayerScore::~PlayerScore()
{
	m_numbers.clear();
}

void PlayerScore::Update()
{
	/*Maths needs to be performed to separate out each value into an integer array,
	as to find the value in the sprite sheet it needs to find an int*/

	int numberOfDigits = log10(score); //Number of digits
	int temp = score; //Temp value used to not affect the actual score value
	for (int i = 0; i < SCORE_CHAR_AMOUNT; i++)
	{
		//Checks to make sure the number of digits hasn't exceeded the number in score
		if (i + 1 > numberOfDigits)
		{
			separatedScore[i] = 0;
		}
		else
		{
			separatedScore[i] = temp % 10;
		}
		temp = temp / 10; //As temp is an int, this will always just cut off the last digit
	}
}

void PlayerScore::Render()
{
	for (int i = 0; i < m_numbers.size(); i++)
	{
		m_numbers[i]->Render(separatedScore[i]);
	}
}

void PlayerScore::IncrementScore(int increment)
{
	score += increment;
	//Only runs update when the score changes
	Update();
}