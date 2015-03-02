#ifndef PLAYER_H_
#define	PLAYER_H_

#include <iostream>
#include "Sprite.h"

class Player
{
public:

	Player(){ this->init(); };

	typedef enum { ALIVE, DEAD, BOOSTING, JUMPING } EPlayerState; // player state

	//The dimensions of the dot
	static const int DOT_WIDTH = 20;
	static const int DOT_HEIGHT = 20;

	//Maximum axis velocity of the dot
	static const int DOT_VEL = 10;
		
	bool init(); // initialization	
	void cleanUp(); // delete Player object

	void jump(){ std::cout << "Player jumping" << std::endl; }; // jump
	void duck(){ std::cout << "Player ducking" << std::endl; }; // duck
	void boost(){ std::cout << "Player boosting" << std::endl; }; // boost
	
	// getters
	int getState(){ return m_ePlayerState; };

	// setters 
	void setState(int state){ m_ePlayerState = (EPlayerState)state; };
		
	//Takes key presses and adjusts the dot's velocity
	void handleEvent(SDL_Event& e);

	//Moves the dot
	void move();

	//Shows the dot on the screen
	void render(Sprite* playerSprite, SDL_Rect* currentClip);

private:
	EPlayerState m_ePlayerState; // Player state

	//The X and Y offsets of the dot
	int mPosX, mPosY;

	//The velocity of the dot
	int mVelX, mVelY;
};

#endif