#include "WorldManager.h"
#include "Scene.h"
#include <iostream>

WorldManager* WorldManager::m_Instance = 0;

WorldManager* WorldManager::getInstance()
{	
	if (m_Instance == nullptr)
		m_Instance = new WorldManager();
	return m_Instance;
}

WorldManager::WorldManager()
{
	this->init();
}

bool WorldManager::init()
{	
	currentRunningScene = nullptr;
	m_eGravitationalPull = GRAVITY_DOWN;
	m_RendererFlip = SDL_FLIP_NONE;
	m_nGameWorldSpeed = WORLD_SPEED;
	return true;
}

WorldManager::~WorldManager()
{
	this->cleanUp();
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

void WorldManager::runWithScene(Scene* scene)
{
	printf("WorldManager: Changing running scene...\n");
	if (currentRunningScene != nullptr)
	{
		delete currentRunningScene;
	}

	currentRunningScene = scene;
	currentRunningScene->run();	
}

void WorldManager::cleanUp()
{
	m_pRenderer = nullptr;
	delete m_Instance;
	m_Instance = nullptr;
}

