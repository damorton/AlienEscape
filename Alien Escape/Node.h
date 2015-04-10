#include "Definitions.h"

class Node
{
public:
	Node();
	virtual ~Node();
	SDL_Rect* getBoundBox(){ return m_BoundingBox; };
	//virtual bool checkCollision(SDL_Rect a, SDL_Rect b);	
	virtual bool checkCollision(SDL_Rect* node);
protected:
	SDL_Rect* m_BoundingBox;
};