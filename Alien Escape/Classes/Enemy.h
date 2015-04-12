#ifndef ENEMY_H
#define	ENEMY_H

#include <iostream>
#include "Definitions.h"
#include "Sprite.h"
#include "Character.h"

class WorldManager;
class Timer;

class Enemy : public Character
{
public:
	typedef enum { ALIVE, DEAD } EEnemyState; // Enemy state
	Enemy(){ this->init(); };
	virtual ~Enemy(){ this->cleanUp(); };
	bool init();
	void cleanUp();
	void handleEvent(SDL_Event& e);
	void move(float timeStep);
	void render();
	void jump();
	int getState(){ return m_eEnemyState; };
	Sprite* getSprite(){ return &m_EnemySprite; };
	void setState(int state){ m_eEnemyState = (EEnemyState)state; };
private:
	EEnemyState m_eEnemyState;
	WorldManager* m_pWorldManager;
	Timer* m_TBoostTimer;		
	int m_nFrame;
	SDL_Rect gSpriteClips[WALKING_ANIMATION_FRAMES];
	Sprite m_EnemySprite;
	bool m_bIsJumping;
	float m_fDeltaTime;	
	float m_fGameSpeed;
	// reminder: release resources in cleanup
};

#endif