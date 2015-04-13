/*
Enemy.h

In game enemy containing Sprite information

@author	David Morton K00179391
@date	13.4.15
*/
#ifndef ENEMY_H
#define	ENEMY_H

//Includes
#include <iostream>
#include "Definitions.h"
#include "Sprite.h"
#include "Character.h"

//Forward declarations
class WorldManager;

class Enemy : public Character
{
public:	
	Enemy(){ this->init(); };
	virtual ~Enemy(){ this->cleanUp(); };

	bool init();
	void cleanUp();

	/*
		Handle input event from game scene

		@param SDL_Event& e input event
	*/
	void handleEvent(SDL_Event& e);

	/*
		Move the enemy in game

		@param float timeStep used for smooth motion
	*/
	void move(float timeStep);

	//Render the Sprite
	void render();
	void jump();	

	/*
		Get Sprite for enemy object

		@return Sprite* sprite for enemy object
	*/
	Sprite* getSprite(){ return &m_pSprite; };
	
private:	
	WorldManager* m_pWorldManager;		
	// reminder: release resources in cleanup
};

#endif