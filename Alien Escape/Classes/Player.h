#ifndef PLAYER_H_
#define	PLAYER_H_

#include <iostream>
#include "Definitions.h"
#include "Sprite.h"
#include "Character.h"

class WorldManager;
class Timer;

class Player : public Character
{
public:	
	Player(){ this->init(); };
	virtual ~Player(){ this->cleanUp(); };
	bool init();
	void cleanUp();		
	void handleEvent(SDL_Event& e);	
	void move(float timeStep);	
	void render();
	void jump();		
	Sprite* getSprite(){ return &m_pSprite; };
	int getDistance(){ return m_nDistanceScore; };
	void applyDamage(int damage){ m_iLives -= damage; };
	int getLives(){ return m_iLives; };
	bool isBoostEnabled(){ return m_bBoostEnabled; };
private:	
	WorldManager* m_pWorldManager;
	Timer* m_TBoostTimer;			
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