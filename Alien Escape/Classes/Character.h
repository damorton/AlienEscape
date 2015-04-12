#ifndef CHARACTER_H_
#define CHARACTER_H_

// includes
#include "Definitions.h"

class Character
{
public:	
	typedef enum { ALIVE, DEAD } EState; // player state
	virtual ~Character(){};
	virtual bool init() = 0; 
	virtual void cleanUp() = 0;
	virtual void handleEvent(SDL_Event& e) = 0;
	virtual void move(float timeStep) = 0;
	virtual void render() = 0;
	int getState(){ return m_eState; };
	void setState(int state){ m_eState = (EState)state; };

	void setPositionX(int x){ m_PosX = x; };
protected:
	EState m_eState;
	int m_PosX;
	int m_PosY;
	int m_VelX;
	int m_VelY;
	int m_nFrame;
	SDL_Rect gSpriteClips[WALKING_ANIMATION_FRAMES];
	Sprite m_pSprite;
	float m_fDeltaTime;
	bool m_bIsJumping;
};

#endif