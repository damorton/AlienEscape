
#ifndef ENEMY_H_
#define ENEMY_H_

// includes
#include "Character.h"

class Enemy : public Character
{
public:	
	Enemy(){ this->init(); }; // constructor 
	~Enemy(){ this->cleanUp(); }; // deconstructor
	virtual bool init(); // initialize the enemy	
	virtual void runAI(); // run Enemy AI
	virtual void update(); // update the Enemy
	virtual void cleanUp(); // house keeping 

	// sprite
	virtual cocos2d::Sprite* getSprite();
	virtual void setSprite(char* pathToFile);
};

#endif