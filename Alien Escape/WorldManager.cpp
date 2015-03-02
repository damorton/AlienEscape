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
	return true;
}

void WorldManager::cleanUp()
{
	m_pRenderer = NULL;
	delete m_Instance;
	m_Instance = NULL;
}

