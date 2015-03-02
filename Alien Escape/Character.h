
#ifndef CHARACTER_H_
#define CHARACTER_H_

// includes
#include "GameObject.h"

class Character : public GameObject
{
public:
	Character(){ this->init(); }; // constructor
	~Character(){ this->cleanUp(); }; // deconstructor	
	
	virtual bool init(); // initialization
	virtual void cleanUp(); // delete Character 
};

#endif