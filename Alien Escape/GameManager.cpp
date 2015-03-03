#include "GameManager.h"
#include "WorldManager.h"
#include "Definitions.h"
#include "Player.h"
#include "Timer.h"

bool GameManager::init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		m_Window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (m_Window == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (m_Renderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}			
			}
		}
	}
		
	m_pPlayer = new Player();
	WorldManager::getInstance()->setRenderer(m_Renderer);
	return success;
}

bool GameManager::start()
{
	//Start up SDL and create window
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
		//Load media
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
		else
		{
			// run game loop
			this->update();
		}
	}

	//Free resources and close SDL
	this->cleanUp();

	return 0;
}

bool GameManager::loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load sprite sheet texture
	if (!m_pPlayer->getSprite()->loadFromFile("Sprites/foo.png"))
	{
		printf("Failed to load walking animation texture!\n");
		success = false;
	}	

	return success;
}

void GameManager::update()
{	
	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;
			
	Timer timer;

	//While application is running
	while (!quit)
	{
		//Handle events on queue
		while (SDL_PollEvent(&e) != 0)
		{
			//User requests quit
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

			m_pPlayer->handleEvent(e);
		}

		//Calculate time step
		float timeStep = timer.getTicks() / 1000.f;

		// Move for timestep
		m_pPlayer->move(timeStep);

		// Restart timer
		timer.start();

		//Clear screen
		SDL_SetRenderDrawColor(WorldManager::getInstance()->getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(WorldManager::getInstance()->getRenderer());
				
		// Render the player
		m_pPlayer->render();

		//Update screen
		SDL_RenderPresent(WorldManager::getInstance()->getRenderer());
	}
}


void GameManager::cleanUp()
{
	delete m_pPlayer;
	m_pPlayer = NULL;

	//Destroy window	
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
	m_Renderer = NULL;
	m_Window = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}