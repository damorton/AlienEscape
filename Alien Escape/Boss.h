
#ifndef BOSS_H_
#define BOSS_H_

// includes
#include "Enemy.h"

class Boss : public Enemy
{
public:
	Boss(){ this->init(); }; // constructor
	~Boss(){ this->cleanUp(); }; // deconstructor
	virtual bool init(); // initialize the Boss
	virtual void runAI(); // run the Boss AI
	virtual void update(); // update the Boss
	virtual void cleanUp();  
	
	// sprite information
	virtual cocos2d::Sprite* getSprite();
	virtual void setSprite(char* pathToFile);
};

#endif