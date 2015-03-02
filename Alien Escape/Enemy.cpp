
//includes
#include "Enemy.h"
#include <iostream>

/*
	Initialization

	@return bool true if initialized succesfully
*/
bool Enemy::init()
{
#ifdef _DEBUG
	CCLOG("Enemy::init() called");
#endif
	// initialize Enemy
	// set game object type	
	setType(EGameOjectType::ENEMY);
	setName("Enemy");
	return true;
}

/*
	get enemy sprite information

	@return cocos2d::Sprite* enemy sprite information
*/
cocos2d::Sprite* Enemy::getSprite()
{
	return m_pCharacterSprite;
}

/*
	set the enemy sptire information

	@param path to file
*/
void Enemy::setSprite(char* pathToFile)
{
	m_pCharacterSprite = cocos2d::Sprite::create(pathToFile);
}

/*
	Run the enemy AI
*/
void Enemy::runAI()
{
	CCLOG("Running Enemy AI");
}

/*
	Update the enemy
*/
void Enemy::update()
{
	CCLOG("Updating Enemy");
}

/*
	Enemy cleanup
*/
void Enemy::cleanUp()
{
#ifdef _DEBUG
	CCLOG("Enemy::cleanUp()");
#endif
}