#ifndef ENEMY_H
#define	ENEMY_H

#include <iostream>
#include "Definitions.h"
#include "Sprite.h"
#include "Character.h"

class WorldManager;

class Enemy : public Character
{
public:	
	Enemy(){ this->init(); };
	virtual ~Enemy(){ this->cleanUp(); };
	bool init();
	void cleanUp();
	void handleEvent(SDL_Event& e);
	void move(float timeStep);
	void render();
	void jump();	
	Sprite* getSprite(){ return &m_pSprite; };
	
private:	
	WorldManager* m_pWorldManager;		
	// reminder: release resources in cleanup
};

#endif