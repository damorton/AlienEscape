#ifndef PLAYER_H_
#define	PLAYER_H_

#include <iostream>
#include "Sprite.h"
#include "SDL.h"

//Walking animation
#define WALKING_ANIMATION_FRAMES 4

#define GRAVITY 60
#define MAX_JUMP_VELOCITY 1500

class Player
{
public:
	typedef enum { ALIVE, DEAD } EPlayerState; // player state
	Player(){ this->init(); };
	virtual ~Player(){ this->cleanUp(); };
	bool init();
	void cleanUp();	
			
	// Max velocity
	int maxVelocity = 640;
	
	// Player actions
	void jump();
		
	// Player state
	void setState(int state){ m_ePlayerState = (EPlayerState)state; };
	int getState(){ return m_ePlayerState; };
	
	// Player sprite
	Sprite* getSprite(){ return &m_PlayerSprite; };
			
	//Takes key presses and adjusts the dot's velocity
	void handleEvent(SDL_Event& e);

	//Moves the dot
	void move(float timeStep);

	//Shows the dot on the screen
	void render();
	
private:
	EPlayerState m_ePlayerState; 
	int m_PosX;
	int m_PosY;
	int m_VelX;
	int m_VelY;
	int m_nFrame;
	int spriteAnimationSpeed;
	SDL_Rect gSpriteClips[WALKING_ANIMATION_FRAMES];
	Sprite m_PlayerSprite;
	bool m_bIsJumping;
	float m_fDeltaTime;
	int m_nNumberOfJumps;
};

#endif