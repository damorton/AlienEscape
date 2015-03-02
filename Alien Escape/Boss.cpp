
#include <iostream>
#include "Boss.h"

/*
	Initialization

	@return bool true if initialized succesfully
*/
bool Boss::init()
{	
#ifdef _DEBUG
	CCLOG("Boss::init()");
#endif
	// initialize boss
	setType(EGameOjectType::BOSS);
	setName("Boss");
	return true;
}

/*
	get the Boss sprite information

	@return cocos2d::Sprite* pointer to character sprite
*/
cocos2d::Sprite* Boss::getSprite()
{
	return m_pCharacterSprite;
}

/*
	set boss sprite information

	@param char* path to file 
*/
void Boss::setSprite(char* pathToFile)
{
	m_pCharacterSprite = cocos2d::Sprite::create(pathToFile);
}

/* Run Boss AI */
void Boss::runAI()
{
	// run the Boss AI
	CCLOG("Running Boss AI");
}

/* Update the Boss */
void Boss::update()
{
	// update the Boss
	CCLOG("Updating Boss");
}

/* Boss clean up */
void Boss::cleanUp()
{	
#ifdef _DEBUG
	CCLOG("Boss::cleanUp() called");
#endif	
}
