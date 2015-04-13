/*
Character.h

Character attributes and basic function structure

@author	David Morton K00179391
@date	13.4.15
*/
#ifndef CHARACTER_H_
#define CHARACTER_H_

// includes
#include "Definitions.h"

class Character
{
public:	
	typedef enum { ALIVE, DEAD } EState; //Character state
	virtual ~Character(){};

	//Pure virtual functions to be implemented by child classes
	virtual bool init() = 0; 
	virtual void cleanUp() = 0;
	virtual void handleEvent(SDL_Event& e) = 0;
	virtual void move(float timeStep) = 0;
	virtual void render() = 0;

	// Getters 
	int getState(){ return m_eState; };

	// Setters
	void setState(int state){ m_eState = (EState)state; };
	void setPositionX(int x){ m_PosX = x; };
protected:
	EState m_eState;
	int m_PosX;
	int m_PosY;
	int m_VelX;
	int m_VelY;
	int m_nFrame;

	//Rects used for sprite clipping and animations
	SDL_Rect gSpriteClips[WALKING_ANIMATION_FRAMES];

	Sprite m_pSprite;
	float m_fDeltaTime;
	bool m_bIsJumping;
};

#endif