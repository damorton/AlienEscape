
#ifndef CHARACTER_H_
#define CHARACTER_H_

// includes
#include "GameObject.h"
#include "cocos2d\cocos\2d\CCSprite.h"

class Character : public GameObject
{
public:
	Character(){ this->init(); }; // constructor
	~Character(){ this->cleanUp(); }; // deconstructor	
	
	virtual bool init(); // initialization
	virtual void cleanUp(); // delete Character 

	virtual cocos2d::Sprite* getSprite() = 0; // return sprite info
	virtual void setSprite(char* pathToFile) = 0; // set sprite info

protected:
	cocos2d::Sprite* m_pCharacterSprite; // cocos Sprite
};

#endif