/*
Player.h

Player object contains Sprite information. Handles game input and 
records players scores

@author	David Morton K00179391
@date	13.4.15
*/
#ifndef PLAYER_H_
#define	PLAYER_H_

//Includes
#include <iostream>
#include "Definitions.h"
#include "Sprite.h"
#include "Character.h"

//Forward Declarations
class WorldManager;
class Timer;

class Player : public Character
{
public:	
	Player(){ this->init(); };
	virtual ~Player(){ this->cleanUp(); };

	//Implement Character functions
	bool init();
	void cleanUp();		
	void handleEvent(SDL_Event& e);	
	void move(float timeStep);	
	void render();
	void jump();		
	void applyDamage(int damage){ m_iLives -= damage; };
	bool isBoostEnabled(){ return m_bBoostEnabled; };
	
	//Getters
	Sprite* getSprite(){ return &m_pSprite; };
	int getDistance(){ return m_nDistanceScore; };	
	int getLives(){ return m_iLives; };	
private:	
	WorldManager* m_pWorldManager;
	Timer* m_TBoostTimer; // Boost timer		

	//Player status
	int m_nNumberOfJumps;
	int m_nDistance;
	int m_nDistanceScore;
	bool m_bIsBoosting;
	bool m_bBoostEnabled;
	float m_fGameSpeed;
	int m_iLives = 3;
	// reminder: release resources in cleanup
};

#endif