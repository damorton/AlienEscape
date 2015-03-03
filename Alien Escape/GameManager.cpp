#include "GameManager.h"
#include "WorldManager.h"
#include "Definitions.h"
#include "Player.h"
#include "Timer.h"

bool GameManager::init()
{
	bool success = true;
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
		
	// Create player
	m_pPlayer = new Player();

	// Store
	WorldManager::getInstance()->setRenderer(m_Renderer);
	return success;
}

bool GameManager::start()
{
	if (!init())
	{
		printf("Failed to initialize!\n");
	}
	else
	{
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
	this->cleanUp();
	return 0;
}

bool GameManager::loadMedia()
{
	bool success = true;

	// Sprites
	if (!m_pPlayer->getSprite()->loadFromFile("Sprites/foo.png"))
	{
		printf("Failed to load walking animation texture!\n");
		success = false;
	}	

	// Fonts
	m_Font = TTF_OpenFont("Fonts/lazy.ttf", 28);
	if (m_Font == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}	
	return success;
}

void GameManager::update()
{	
	bool quit = false;
	SDL_Event e;			
	Timer fpsTimer;
	Timer capTimer;
	Timer deltaTimer;
	fpsTimer.start();	
	int countedFrames = 0;	
	if (DEBUG) this->initDebug();

	// -------------------- GAME LOOP START --------------------
	while (!quit)
	{
		// -------------------- INPUT --------------------		
		capTimer.start();				
		while (SDL_PollEvent(&e) != 0)
		{			
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
			m_pPlayer->handleEvent(e);
		}	

		// -------------------- LOGIC --------------------
		avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
		if (avgFPS > 2000000)
		{
			avgFPS = 0;
		}
		float timeStep = deltaTimer.getTicks() / 1000.f;
		m_pPlayer->move(timeStep);
		deltaTimer.start();

		// -------------------- RENDER --------------------
		SDL_SetRenderDrawColor(WorldManager::getInstance()->getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(WorldManager::getInstance()->getRenderer());		
		if (DEBUG) this->renderDebug();
		m_pPlayer->render();
		SDL_RenderPresent(WorldManager::getInstance()->getRenderer());

		// -------------------- DELAY --------------------
		++countedFrames;
		int frameTicks = capTimer.getTicks();
		if (frameTicks < SCREEN_TICK_PER_FRAME)
		{
			SDL_Delay(SCREEN_TICK_PER_FRAME - frameTicks);
		}
	}
	// -------------------- GAME LOOP END --------------------
}

void GameManager::initDebug()
{
	//Set text color as black
	textColor = { 0, 0, 0, 255 };	
}

void GameManager::renderDebug()
{
	//Set text to be rendered
	fpsText.str("");
	fpsText << "FPS: " << avgFPS;
	if (!m_FPSTextTexture.loadFromRenderedText(fpsText.str().c_str(), textColor, m_Font))
	{
		printf("Unable to render FPS texture!\n");
	}
	m_FPSTextTexture.render(PADDING, PADDING);


	// Gravity Info
	gravityText.str("");	
	if(WorldManager::getInstance()->getGravityDirection() == GRAVITY_DOWN) gravityText << "Gravity: DOWN";
	else gravityText << "Gravity: UP";	
	if (!m_GravityTextTexture.loadFromRenderedText(gravityText.str().c_str(), textColor, m_Font))
	{
		printf("Unable to render FPS texture!\n");
	}
	m_GravityTextTexture.render(PADDING, PADDING + m_FPSTextTexture.getHeight() + PADDING);

	// Distance
	distanceText.str("");
	distanceText << "Distance: " << m_pPlayer->getDistance() << "m";
	if (!m_DistanceTextTexture.loadFromRenderedText(distanceText.str().c_str(), textColor, m_Font))
	{
		printf("Unable to render FPS texture!\n");
	}
	m_DistanceTextTexture.render(PADDING, PADDING + m_FPSTextTexture.getHeight() + PADDING + m_GravityTextTexture.getHeight() + PADDING);
	
}


void GameManager::cleanUp()
{
	//Free loaded images
	m_FPSTextTexture.free();
	m_GravityTextTexture.free();
	m_DistanceTextTexture.free();

	// Delete Player
	delete m_pPlayer;
	m_pPlayer = NULL;

	//Free global font
	TTF_CloseFont(m_Font);
	m_Font = NULL;

	//Destroy window	
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
	m_Renderer = NULL;
	m_Window = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}