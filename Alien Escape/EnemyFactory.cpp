
#include "EnemyFactory.h"
#include "Boss.h"

/*
	Initialization

	@return bool true if initialized succesfully
*/
bool EnemyFactory::init()
{
#ifdef _DEBUG
	CCLOG("EnemyFactory::init() called");
#endif
	return true;
}

/*
	Create Enemy
		
	@return pointer to the enemy object
*/
std::shared_ptr<Enemy> EnemyFactory::createEnemy()
{	
	// create Enemy
	return std::shared_ptr<Enemy>(new Enemy());
}

/*
	Create Boss

	@return Boss object
*/
std::shared_ptr<Boss> EnemyFactory::createBoss()
{	
	// create Boss
	return std::shared_ptr<Boss>(new Boss());
}

/*
	Enemy factory clean up
*/
void EnemyFactory::cleanUp()
{
#ifdef _DEBUG
	CCLOG("EnemyFactory::cleanUp() called");
#endif
}
