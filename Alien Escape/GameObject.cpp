
// includes
#include <iostream>
#include "GameObject.h"
#include "cocos2d.h"

/*
	Initialization

	@return bool true if initialized succesfully
*/
bool GameObject::init()
{
#ifdef _DEBUG
	CCLOG("GameObject::init()");
#endif

	// get game screen size and origin
	visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	origin = cocos2d::Director::getInstance()->getVisibleOrigin();
	
	setType(EGameOjectType::OBJECT);
	setName("Game Object");
	return true;
}

void GameObject::cleanUp()
{
#ifdef _DEBUG
	CCLOG("GameObject::cleanUp() called");
#endif
}
