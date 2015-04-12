#ifndef CHARACTER_H_
#define CHARACTER_H_

// includes
//#include "GameObject.h"

class Character
{
public:	
	virtual bool init() = 0; // initialization
	virtual void cleanUp() = 0; // delete Character 
protected:
	int m_PosX;
	int m_PosY;
	int m_VelX;
	int m_VelY;
};

#endif