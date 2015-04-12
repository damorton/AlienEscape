#include "WorldManager.h"
#include "Scene.h"
#include "Definitions.h"
#include "DAO\GameDAO.h"
#include "DAO\StoryPoint.h"
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
	if (!init())
	{
		printf("Failed to initialize Game Scene!\n");
	}
}

bool WorldManager::init()
{	
	bool success = true;

	// Game DAO
	IGameDAO* dao = new GameDAO();
	if (!isXMLFileExist())
	{
		dao->create();
		loadDefaultConfig(dao);
	}

	std::shared_ptr<std::vector<StoryPoint>> storyPoints = dao->read();

	std::cout << storyPoints->at(0).getStoryText()->getText() << std::endl;

	for (int i = 0; i<storyPoints->at(0).getStoryChoices()->size(); i++)
	{
		std::cout << storyPoints->at(0).getStoryChoices()->at(i).getText() << std::endl;
	}



	//dao->update(storyPoints);

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
		m_Window = SDL_CreateWindow("Alien Escape", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

bool WorldManager::isXMLFileExist()
{
	// Check if the XML file exists by getting a writable path
	// based on the device the game is running on.
	std::string filepath = "";
	filepath.append(XMLDOC);
	//CCLOG("%s", filepath.c_str());

	// Try and open the file at filepath
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
	std::shared_ptr<std::vector<StoryPoint>> storyPoints = dao->read();

	StoryPoint storyPoint;
	storyPoint.setStoryText("You Open on a courtyard, it is dark. You see a Door");
	storyPoint.addStoryChoice("1. Open Door");
	storyPoint.addStoryChoice("2. Run Away");

	storyPoints->push_back(storyPoint);
	dao->update(storyPoints);
}

WorldManager::~WorldManager()
{
	this->cleanUp();
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

