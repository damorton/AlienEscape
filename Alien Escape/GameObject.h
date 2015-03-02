
#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "Sprite.h"

typedef enum { OBJECT, PLAYER, ENEMY, BOSS } EGameOjectType;

class GameObject : public Sprite
{
public:
	GameObject(){ this->init(); };
	~GameObject(){ this->cleanUp(); };
	virtual bool init();
	virtual void cleanUp();

	// getters
	float getPositionX(){ return m_fPositionX; };
	float getPositionY(){ return m_fPositionY; };

	float getScaleX(){ return m_fScaleX; };
	float getScaleY(){ return m_fScaleY; };

	float getRotationX(){ return m_fRotationX; };
	float getRotationY(){ return m_fRotationY; };

	bool isCollided(){ return m_bIsCollided; };

	char* getName(){ return m_strName; };

	// get game object type
	EGameOjectType getType(){ return m_eType; };

	// setters
	void setPositionX(float x){ m_fPositionX = x; };
	void setPositionY(float y){ m_fPositionY = y; };
	void setPosition(float x, float y){ m_fPositionX = x; m_fPositionY = y; };

	void setScaleX(float x){ m_fScaleX = x; };  
	void setScaleY(float y){ m_fScaleY = y; }; 
	void setScale(float x, float y){ m_fScaleX = x; m_fScaleY = y; };

	void setRotationX(float x){ m_fRotationX = x; }
	void setRotationY(float y){ m_fRotationY = y; }
	void setRotation(float x, float y){ m_fRotationX = x; m_fRotationY = y; };

	void setBoundingBox(cocos2d::Rect boundingBox){ m_boundingBoxRect = boundingBox; };

	void setCollided(bool isCollided){ m_bIsCollided = isCollided; }

	// set game object type
	void setType(EGameOjectType type){ m_eType = type; };

	void setName(char* name){ m_strName = name; };

protected:
	// 2d coordinate position
	float m_fPositionX;
	float m_fPositionY;

	// scale data
	float m_fScaleX;
	float m_fScaleY;

	// rotation data
	float m_fRotationX;
	float m_fRotationY;

	// game objects bounding box
	cocos2d::Rect m_boundingBoxRect;
		
	// collisions
	bool m_bIsCollided;

	// name of the object
	char* m_strName;
	
	cocos2d::Size visibleSize;
	cocos2d::Vec2 origin;
	cocos2d::Vec2 playerPosition;
	
	EGameOjectType m_eType;
};

#endif