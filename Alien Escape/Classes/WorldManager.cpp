/*
WorldManager.cpp

WorldManager is a singleton class used to access all game information from anywhere in the
system. It also manages collisions between objects in the game by checking the game
objects bounding boxes. The WorldManager communicates directly with the games Data Access object
allowing data to be read from, and written to XML files stored on the device. All aspects of the game can
be modified by the World Manager.

@author	David Morton K00179391
@date	13.4.15
*/
//Includes
#include <iostream>
#include "WorldManager.h"
#include "MenuScene.h"
#include "Enemy.h"
#include "DAO\Record.h"

WorldManager* WorldManager::m_Instance = 0;

WorldManager* WorldManager::getInstance()
{	
	//Create the World Manager and return it
	if (m_Instance == nullptr)
		m_Instance = new WorldManager();
	return m_Instance;
}

WorldManager::WorldManager()
{
	if (!init())
	{
		printf("Failed to initialize Game Scene!\n");
	}
}

WorldManager::~WorldManager()
{
	//Clean up all resources created by the World Manager
	this->cleanUp();
}

bool WorldManager::init()
{	
	bool success = true;

	//Create Game DAO is it dosent already exist
	if (m_pGameDAO == nullptr)
	{
		m_pGameDAO = new GameDAO();
	}
	
	//Check id the XML file exists
	if (!isXMLFileExist())
	{
		m_pGameDAO->create();
		loadDefaultConfig(m_pGameDAO);
	}

	std::cout << "Game XML Configuration Settings\n-------------------------------" << std::endl;
	std::shared_ptr<std::vector<Record>> resources = m_pGameDAO->read();		

	for (int i = 0; i < resources->size(); i++)
	{
		for (int j = 0; j < resources->at(i).getResources()->size(); j++)
		{
			std::cout << resources->at(i).getResources()->at(j).getName() << " -> " << resources->at(i).getResources()->at(j).getValue() << std::endl;
		}
	}
	
	std::cout << "\nGame Debug\n---------" << std::endl;
	//m_pGameDAO->update(resources);

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}
		m_Window = SDL_CreateWindow(this->readDAO("GameName").c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (m_Window == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (m_Renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				// PNG images
				SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}

				// Truetype Fonts
				if (TTF_Init() == -1)
				{
					printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
					success = false;
				}
			}
		}
	}

	currentRunningScene = nullptr;
	m_eGravitationalPull = GRAVITY_DOWN;
	m_RendererFlip = SDL_FLIP_NONE;
	m_nGameWorldSpeed = WORLD_SPEED;
		
	return success;
}

std::string WorldManager::readDAO(std::string name)
{
	std::shared_ptr<std::vector<Record>> resources = m_pGameDAO->read();

	for (int i = 0; i < resources->size(); i++)
	{
		for (int j = 0; j < resources->at(i).getResources()->size(); j++)
		{
			if (resources->at(i).getResources()->at(j).getName() == name)
			{
				return resources->at(i).getResources()->at(j).getValue();
			}						
		}
	}
}

bool WorldManager::isXMLFileExist()
{	
	std::string filepath = "";
	filepath.append(XMLDOC);
		
	FILE *fp;
	fopen_s(&fp, filepath.c_str(), "r");
	bool bRet = false;

	// If the file can be opened, it exists
	if (fp)
	{
		bRet = true;
		fclose(fp);
	}
	return bRet;
}

void WorldManager::loadDefaultConfig(IGameDAO* dao)
{
	std::shared_ptr<std::vector<Record>> resources = dao->read();

	// Menu Scene Config
	Record gameConfig;
	gameConfig.setName("GameConfig");
	gameConfig.addResource("GameName", "Alien Escape");	
	gameConfig.addResource("GameFont", "Resources/Fonts/go3v2.ttf");
	resources->push_back(gameConfig);

	// Menu Scene Config
	Record menuSceneConfig;	
	menuSceneConfig.setName("MenuScene");	
	menuSceneConfig.addResource("MenuSceneStartLabel", "Start Game");
	menuSceneConfig.addResource("MenuSceneBackground", "Resources/Backgrounds/MenuBackground.png");	
	resources->push_back(menuSceneConfig);

	// Menu Scene Config
	Record gameSceneConfig;
	gameSceneConfig.setName("GameScene");
	gameSceneConfig.addResource("GameScenePlayer", "Resources/Sprites/Player.png");
	gameSceneConfig.addResource("GameSceneEnemyAlien", "Resources/Sprites/EnemyAlien.png");
	gameSceneConfig.addResource("GameSceneBackgroundA", "Resources/Backgrounds/BackgroundA.png");
	gameSceneConfig.addResource("GameSceneBackgroundB", "Resources/Backgrounds/BackgroundB.png");
	gameSceneConfig.addResource("GameSceneMidgroundA", "Resources/Backgrounds/MidgroundA.png");
	gameSceneConfig.addResource("GameSceneMidgroundB", "Resources/Backgrounds/MidgroundB.png");	
	resources->push_back(gameSceneConfig);

	// HUD Config
	Record HUDConfig;
	HUDConfig.setName("HUDConfig");
	HUDConfig.addResource("HUDConfigPause", "Resources/Buttons/Pause.png");
	resources->push_back(HUDConfig);

	dao->update(resources);
}

bool WorldManager::checkCollisions()
{
	bool collision = false;

	for (int i = 0; i < m_vpGameNodes.size(); i++)
	{
		Enemy* tempEnemy = (Enemy*)m_vpGameNodes.at(i);
		if (m_pPlayer->getSprite()->checkCollision(tempEnemy->getSprite()->getBoundBox()) && tempEnemy->getState() == Character::ALIVE)
		{		
			printf("Collision Detected!\n");
			tempEnemy->setState(Character::DEAD);

			m_pPlayer->applyDamage(1);
			if (m_pPlayer->getLives() < 0)
			{
				m_pPlayer->setState(Character::DEAD);
			}				
			
			if (m_pPlayer->getState() == Character::DEAD)
			{
				printf("Game Over\n");
				collision = true;
				m_vpGameNodes.clear();
				// Game over
				MenuScene* menuScene = new MenuScene();
				WorldManager::getInstance()->runWithScene(menuScene);
			}			
		}
	}

	return collision;
}

void WorldManager::resetGame()
{	
	m_eGravitationalPull = GRAVITY_DOWN;
	m_RendererFlip = SDL_FLIP_NONE;
	m_nGameWorldSpeed = WORLD_SPEED;
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
	printf("Gravity Flipped\n");
}

void WorldManager::runWithScene(Scene* scene)
{
	printf("WorldManager: Changing running scene...\n");
	if (currentRunningScene != nullptr)
	{		
		currentRunningScene->cleanup();
		delete currentRunningScene;
	}

	currentRunningScene = scene;
	currentRunningScene->run();		
}

void WorldManager::cleanUp()
{
	delete m_Instance;
	m_Instance = nullptr;

	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
	m_Renderer = NULL;
	m_Window = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	
}

