// includes 
#include <iostream>
#include "CollisionManager.h"
#include "Player.h"
#include "Boss.h"

// implementation
CollisionManager* CollisionManager::m_Instance = 0;

/*
	Get instance of CollisionManager Singleton

	@return CollisionManager instance
*/
CollisionManager* CollisionManager::getInstance()
{
	// if the pointer is null set it to an instance 
	// of the WorldManager
	if (m_Instance == 0)
		m_Instance = new CollisionManager();
	return m_Instance;
}

/*
	Initialization

	@return bool true if initialized succesfully
*/
bool CollisionManager::init()
{
#ifdef _DEBUG
	CCLOG("CollisionManager::init() called");
#endif
	// initialize the collision manager
	return true;
}

/* 
	Register with the collision manager 

	@param GameObject obj
*/
void CollisionManager::registerWithCollisionManager(std::shared_ptr<GameObject> obj)
{
#ifdef _DEBUG
	CCLOG("CollisionManager::registerWithCollisionManager() called");
#endif
	// store GameOject in vector when registered
	m_pvGameObjects.push_back(obj); 
};

/* 
	Register the player object 
	
	@param GameObject obj
*/
void CollisionManager::registerPlayer(std::shared_ptr<Player> player)
{	
#ifdef _DEBUG
	CCLOG("CollisionManager::registerPlayer() called");
#endif
	// store the Player object when registered
	m_pPlayer = player; 
};

/*
	Collision detection, check player against all other 
	registered game objects

	@return bool true if collision, false if not
*/
bool CollisionManager::checkCollisons()
{
	// loop through the CollisionManagers game object vector
	// check each object and cast using its enum type
	for (int i = 0; i < (int) m_pvGameObjects.size(); i++)
	{		
		// enemy game object
		if (m_pvGameObjects.at(i)->getType() == EGameOjectType::ENEMY)
		{
			// check the game objects type and cast appropriatly
			// use std::static_pointer_cast to cast shared pointers
			std::shared_ptr<Enemy> tempEnemy = std::static_pointer_cast<Enemy>(m_pvGameObjects.at(i));
			CCLOG("Checking collision between %s and %s",m_pPlayer->getName(), tempEnemy->getName());
			if (m_pPlayer->collidesWith(tempEnemy))
			{
				CCLOG("Collision detected! the %s hit the %s! :/", m_pPlayer->getName(), tempEnemy->getName());
				return true;
			}			
		}

		// boss game object
		if (m_pvGameObjects.at(i)->getType() == EGameOjectType::BOSS)
		{
			// check the game objects type and cast appropriatly
			// use std::static_pointer_cast to cast shared pointers
			std::shared_ptr<Enemy> tempEnemy = std::static_pointer_cast<Enemy>(m_pvGameObjects.at(i));
			CCLOG("Checking collision between %s and %s", m_pPlayer->getName(), tempEnemy->getName());
			if (m_pPlayer->collidesWith(tempEnemy))
			{
				CCLOG("Collision detected! the %s hit the %s! :/", m_pPlayer->getName(), tempEnemy->getName());
				return true;
			}			
		}

		// can add checks for wall? bullet? coins?
		
	}
	CCLOG("No collisions detected. We're safe :)");
	return false;
}

/*
	CollisionManager hosue keeping
*/
void CollisionManager::cleanUp()
{
	// all objects created in the collision manager are using shared pointers
	// so there is no need to delete the objects
	delete m_Instance;
}