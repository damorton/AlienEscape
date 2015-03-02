#include "WorldManager.h"
#include "CollisionManager.h"
#include "EnemyFactory.h"
#include "Player.h"
#include "Enemy.h"
#include "Boss.h"

// implementation
WorldManager* WorldManager::m_Instance = 0;

/*
	Get instance of WorldManager Singleton

	@return WorldManager instance
*/
WorldManager* WorldManager::getInstance()
{
	// if the pointer is null set it to an instance 
	// of the WorldManager
	if (m_Instance == 0)
		m_Instance = new WorldManager();
	return m_Instance;
}

/*
	Initialization

	@return bool true if initialized succesfully
*/
bool WorldManager::init()
{	
#ifdef _DEBUG
	CCLOG("WorldManager::init() called");
#endif

	// create the game objects and store them inside the singleton
	m_pPlayer = createPlayer(); // Player
	CollisionManager::getInstance()->registerPlayer(m_pPlayer); // register player
		
	m_pIEnemyFactory = createEnemyFactory(); // EnemyFactory
	
	// create and add enemies to vector	
	m_pEnemy1 = m_pIEnemyFactory->createEnemy();
	m_pvEnemies.push_back(m_pEnemy1);	// add to enemy vector
	CollisionManager::getInstance()->registerWithCollisionManager(m_pEnemy1); // register with collision manager

	m_pEnemy2 = m_pIEnemyFactory->createEnemy();
	m_pvEnemies.push_back(m_pEnemy2); // add to enemy vector
	CollisionManager::getInstance()->registerWithCollisionManager(m_pEnemy2); // register with collision manager

	m_pEnemy3 = m_pIEnemyFactory->createEnemy();
	m_pvEnemies.push_back(m_pEnemy3); // add to enemy vector
	CollisionManager::getInstance()->registerWithCollisionManager(m_pEnemy3); // register with collision manager

	m_pBoss = m_pIEnemyFactory->createBoss(); // Boss	
	CollisionManager::getInstance()->registerWithCollisionManager(m_pBoss); // register boss with collision manager

	

	return true;
}

/*
	Create Player

	@return Player object
*/
std::shared_ptr<Player> WorldManager::createPlayer()
{
#ifdef _DEBUG
	CCLOG("WorldManager::createPlayer() called");
#endif
	// create Player
	return std::shared_ptr<Player>(new Player());
}

/*
	Create EnemyFactory

	@return EnemyFactory object
*/
std::shared_ptr<IEnemyFactory> WorldManager::createEnemyFactory()
{
#ifdef _DEBUG
	CCLOG("WorldManager::createEnemyFactory() called");
#endif
	// create EnemyFactory
	return std::shared_ptr<IEnemyFactory>(new EnemyFactory());
}


void WorldManager::cleanUp()
{
#ifdef _DEBUG
	CCLOG("WorldManager::cleanUp() called");
#endif		

	// delete all objects created in the world manager using - new	
	// no need to delete objects created in WorldManager because 
	// shared pointers are used. Only the singleton instance needs
	// deleting.
	delete m_Instance;
}

