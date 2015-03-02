
#ifndef GAMEOBJECT_H_
#define GAMEOBJECT_H_

#include "Sprite.h"

typedef enum { OBJECT, PLAYER, ENEMY} EGameOjectType;

class GameObject : public Sprite
{
protected:
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
	
	void setCollided(bool isCollided){ m_bIsCollided = isCollided; }

	// set game object type
	void setType(EGameOjectType type){ m_eType = type; };

	void setName(char* name){ m_strName = name; };
	

	//Sets the dot
	void init(int x, int y, int lvlWidth, int lvlHeight);

	//Handles keypress
	void handle_input();

	//Moves the dot
	void move();

	//Shows the dot
	void show();

	//Sets the camera over the dot
	void set_camera();

	//Gets the dot's collision box
	operator SDL_Rect();

	// 2d coordinate position
	float m_fPositionX;
	float m_fPositionY;

	// scale data
	float m_fScaleX;
	float m_fScaleY;

	// rotation data
	float m_fRotationX;
	float m_fRotationY;
		
	// collisions
	bool m_bIsCollided;

	// name of the object
	char* m_strName;
		
	EGameOjectType m_eType;

private:
	//The collision box of the dot
	SDL_Rect box;

	//The velocity of the dot
	int xVel, yVel;

	//The current level dimensions
	int curLvlWidth;
	int curLvlHeight;
};

#endif