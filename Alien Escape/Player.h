#ifndef PLAYER_H_
#define	PLAYER_H_

#include <iostream>
#include "Definitions.h"
#include "Sprite.h"

class WorldManager;
class Timer;

class Player
{
public:
	typedef enum { ALIVE, DEAD } EPlayerState; // player state
	Player(){ this->init(); };
	virtual ~Player(){ this->cleanUp(); };
	bool init();
	void cleanUp();		
	void handleEvent(SDL_Event& e);	
	void move(float timeStep);	
	void render();
	void jump();		
	int getState(){ return m_ePlayerState; };	
	Sprite* getSprite(){ return &m_PlayerSprite; };
	int getDistance(){ return m_nDistanceScore; };
	void setState(int state){ m_ePlayerState = (EPlayerState)state; };	
private:
	EPlayerState m_ePlayerState; 
	WorldManager* m_pWorldManager;
	Timer* m_TBoostTimer;
	int m_PosX;
	int m_PosY;
	int m_VelX;
	int m_VelY;
	int m_nFrame;
	SDL_Rect gSpriteClips[WALKING_ANIMATION_FRAMES];
	Sprite m_PlayerSprite;
	bool m_bIsJumping;
	float m_fDeltaTime;
	int m_nNumberOfJumps;
	int m_nDistance;
	int m_nDistanceScore;
	bool m_bIsBoosting;
	bool m_bBoostEnabled;
	float m_fGameSpeed;
	// reminder: release resources in cleanup
};

#endif