#include "Collisions.h"
#include "Character.h"

//Initialise instance to nullptr
Collisions* Collisions::m_instance = nullptr;

Collisions::Collisions()
{

}

Collisions::~Collisions()
{
	m_instance = nullptr;
}

Collisions* Collisions::Instance()
{
	//Checks if the m_instance pointer has been set up correctly
	if (!m_instance)
	{
		m_instance = new Collisions;
	}

	return m_instance;
}

bool Collisions::Circle(Character* character1, Character* character2)
{
	//Calculates the vector between the two objecets
	Vector2D vec = Vector2D((character1->GetPosition().x - character2->GetPosition().x), (character1->GetPosition().y - character2->GetPosition().y));
	//Calculates the length of the vector
	double distance = sqrt((vec.x * vec.x) + (vec.y * vec.y));
	//Get the collision radius of each character and accumulate them
	double combined_distance = (character1->GetCollisionRadius() + character2->GetCollisionRadius());
	//Check whether the distance is shorter than the accumlated collision radii
	return distance < combined_distance;
}


bool Collisions::Box(Rect2D rect1, Rect2D rect2)
{
	//Checking if the boxes overlap with each other
	if (rect1.x + (rect1.width / 2) > rect2.x &&
		rect1.x + (rect1.width / 2) < rect2.x + rect2.width &&
		rect1.y + (rect1.height / 2) > rect2.y &&
		rect1.y + (rect1.height / 2) < rect2.y + rect2.height)
	{
		return true;
	}
	return false; //Only runs if not true, no else needed
}