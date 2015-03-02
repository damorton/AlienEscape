
// includes
#include <iostream>
#include "Character.h"

/*
	Initialization

	@return bool true if initialized succesfully
*/
bool Character::init()
{
#ifdef _DEBUG
	CCLOG("Character::init()");
#endif	
	// initialize Character			
	return true;
}

void Character::cleanUp()
{	
#ifdef _DEBUG
	CCLOG("Character::cleanUp()");
#endif
	
}
