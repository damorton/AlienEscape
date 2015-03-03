#include "WorldManager.h"

WorldManager* WorldManager::m_Instance = 0;

WorldManager* WorldManager::getInstance()
{	
	if (m_Instance == 0)
		m_Instance = new WorldManager();
	return m_Instance;
}

bool WorldManager::init()
{	
	gravityDirection = GRAVITY_DOWN;
	return true;
}

void WorldManager::flipGravity()
{
	if (gravityDirection == GRAVITY_DOWN) gravityDirection = GRAVITY_UP;
	else if (gravityDirection == GRAVITY_UP) gravityDirection = GRAVITY_DOWN;
}

void WorldManager::cleanUp()
{
	m_pRenderer = NULL;
	delete m_Instance;
	m_Instance = NULL;
}

