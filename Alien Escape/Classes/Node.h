#ifndef NODE_H
#define NODE_H
/*
Node.h

Node is a game object and contains the bounding box for 
all objects created in the game. Also calculates collisions

@author	David Morton K00179391
@date	13.4.15
*/
#include "Definitions.h"

class Node
{
public:
	Node();
	virtual ~Node();

	/*
		Return the game nodes bounding box

		@return SDL_Rect bounding box for node
	*/
	SDL_Rect* getBoundBox(){ return m_BoundingBox; };

	/*
		Nodes collision detection checks coordinate values 
		for parameter rect against its values to determine
		collisions.

		@param SDL_Rect* node is a pointer to a game node
	*/
	//virtual bool checkCollision(SDL_Rect a, SDL_Rect b);	
	virtual bool checkCollision(SDL_Rect* node);

	//Getters
	virtual int getPositionX(){ return m_BoundingBox->x; };
	virtual int getPositionY(){ return m_BoundingBox->y; };
protected:
	SDL_Rect* m_BoundingBox; //Bounding Box	
};

#endif