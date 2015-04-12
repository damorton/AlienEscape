
#ifndef IENEMYFACTORY_H_
#define IENEMYFACTORY_H_

// includes
#include <memory>

// forward declarations
class Enemy;
class Boss;

/* IEnemyFactory Interface */
class IEnemyFactory
{
public:	
	// pure virtual methods need to be implemented in sub classes
	virtual bool init() = 0;
	virtual std::shared_ptr<Enemy> createEnemy() = 0;
	virtual std::shared_ptr<Boss> createBoss() = 0;
	virtual void cleanUp() = 0;
};

#endif