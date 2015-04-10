#include "Node.h"

Node::Node()
{
	m_BoundingBox = new SDL_Rect();
	m_BoundingBox->x = 0;
	m_BoundingBox->y = 0;
	m_BoundingBox->w = 0;
	m_BoundingBox->h = 0;
}

Node::~Node()
{	
	delete m_BoundingBox;
	m_BoundingBox = nullptr;	
}

/*
bool checkCollision(SDL_Rect a, SDL_Rect b)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}
*/

bool Node::checkCollision(SDL_Rect* node)
{
	//The sides of the rectangles
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = m_BoundingBox->x;
	rightA = m_BoundingBox->x + m_BoundingBox->w;
	topA = m_BoundingBox->y;
	bottomA = m_BoundingBox->y + m_BoundingBox->h;

	//Calculate the sides of rect B
	leftB = node->x;
	rightB = node->x + node->w;
	topB = node->y;
	bottomB = node->y + node->h;

	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}


