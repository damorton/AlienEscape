#ifndef PLAYER_H_
#define	PLAYER_H_

// includes
#include <iostream>
#include "Character.h" // inherit from Character

class Player : public Character
{
public:
	Player(){ this->init(); }; // constructor
	~Player(){ this->cleanUp(); }; // deconstructor
	virtual bool init(); // initialization
	virtual bool collidesWith(std::shared_ptr<GameObject> obj){ return false; }; // collision detection
	void jump(){ std::cout << "Player jumping" << std::endl; }; // jump
	void duck(){ std::cout << "Player ducking" << std::endl; }; // duck
	void boost(){ std::cout << "Player boosting" << std::endl; }; // boost
	virtual void update(); // update Player
	virtual void cleanUp(); // delete Player object
	
	// sprite
	virtual cocos2d::Sprite* getSprite();
	virtual void setSprite(char* pathToFile);

	// getters
	int getState(){ return m_ePlayerState; };

	// setters 
	void setState(int state){ m_ePlayerState = (EPlayerState)state; };

	typedef enum { ALIVE, DEAD, BOOSTING, JUMPING } EPlayerState; // player state
private:	
	EPlayerState m_ePlayerState; // Player state

};

#endif