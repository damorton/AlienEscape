
#ifndef ENEMYFACTORY_H_
#define	ENEMYFACTORY_H_

#include <iostream>
#include "IEnemyFactory.h"

/*
	EnemyFactory used to create enemies inherits from the 
	Interface Enemy Factory
*/
class EnemyFactory : public IEnemyFactory
{
public:	
	EnemyFactory(){ this->init(); }; // constructor
	~EnemyFactory(){ this->cleanUp(); }; // deconstructor
	virtual bool init(); // initialization	
	virtual std::shared_ptr<Enemy> createEnemy(); // create enemy
	virtual std::shared_ptr<Boss> createBoss(); // create Boss
	virtual void cleanUp(); // delete EnemyFactory	

private:
	enum EEnemyType { ENEMY, BOSS }; // types of enemies	
};

#endif

