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
	m_eGravitationalPull = GRAVITY_DOWN;
	m_RendererFlip = SDL_FLIP_NONE;
	m_nGameWorldSpeed = WORLD_SPEED;
	return true;
}

void WorldManager::flipGravity()
{
	if (m_eGravitationalPull == GRAVITY_DOWN)
	{
		m_eGravitationalPull = GRAVITY_UP;
		m_RendererFlip = SDL_FLIP_VERTICAL;
	}
	else if (m_eGravitationalPull == GRAVITY_UP)
	{
		m_eGravitationalPull = GRAVITY_DOWN;
		m_RendererFlip = SDL_FLIP_NONE;
	}	
}

void WorldManager::cleanUp()
{
	m_pRenderer = NULL;
	delete m_Instance;
	m_Instance = NULL;
}

