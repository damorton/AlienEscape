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
	//std::shared_ptr<Player> m_pPlayer(new Player());

	// Store
	m_pWorldManager = WorldManager::getInstance();
	m_pWorldManager->setRenderer(m_Renderer);
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
	m_Font = TTF_OpenFont("Fonts/go3v2.ttf", 28);
	if (m_Font == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}	

	//Load background texture
	if (!m_BackgroundA.loadFromFile("Backgrounds/BackgroundA.png"))
	{
		printf("Failed to load background texture!\n");
		success = false;
	}
	if (!m_BackgroundB.loadFromFile("Backgrounds/BackgroundB.png"))
	{
		printf("Failed to load background texture!\n");
		success = false;
	}
	if (!m_MidgroundA.loadFromFile("Backgrounds/MidgroundA.png"))
	{
		printf("Failed to load background texture!\n");
		success = false;
	}
	if (!m_MidgroundB.loadFromFile("Backgrounds/MidgroundB.png"))
	{
		printf("Failed to load background texture!\n");
		success = false;
	}

	return success;
}

void GameManager::update()
{	
	bool quit = false;
	SDL_Event e;
	float backgroundAscrollingOffset = 0;
	float backgroundBscrollingOffset = SCREEN_WIDTH;
	float midgroundAscrollingOffset = 0;
	float midgroundBscrollingOffset = SCREEN_WIDTH;
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

		// Scroll background A
		backgroundAscrollingOffset -= m_pWorldManager->getGameWorldSpeed();
		if (backgroundAscrollingOffset < -SCREEN_WIDTH)
		{
			backgroundAscrollingOffset = SCREEN_WIDTH;
		}

		// Scroll background B
		backgroundBscrollingOffset -= m_pWorldManager->getGameWorldSpeed();
		if (backgroundBscrollingOffset < -SCREEN_WIDTH)
		{
			backgroundBscrollingOffset = SCREEN_WIDTH;
		}

		// Scroll midground A
		midgroundAscrollingOffset -= m_pWorldManager->getGameWorldSpeed() - 1.0f;
		if (midgroundAscrollingOffset < -SCREEN_WIDTH)
		{
			midgroundAscrollingOffset = SCREEN_WIDTH;
		}

		// Scroll midground B
		midgroundBscrollingOffset -= m_pWorldManager->getGameWorldSpeed() - 1.0f;
		if (midgroundBscrollingOffset < -SCREEN_WIDTH)
		{
			midgroundBscrollingOffset = SCREEN_WIDTH;
		}
		

		// -------------------- RENDER --------------------
		SDL_SetRenderDrawColor(m_pWorldManager->getRenderer(), 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(m_pWorldManager->getRenderer());		
				
		// Render background A
		m_BackgroundA.render(backgroundAscrollingOffset, 0);

		// Render background B
		m_BackgroundB.render(backgroundBscrollingOffset, 0);

		// Render background A
		m_MidgroundA.render(midgroundAscrollingOffset, 0);

		// Render background B
		m_MidgroundB.render(midgroundBscrollingOffset, 0);

		if (DEBUG) this->renderDebug();
		m_pPlayer->render();
		SDL_RenderPresent(m_pWorldManager->getRenderer());

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
	//Set text color as White
	textColor = COLOR_WHITE;	
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
	if(m_pWorldManager->getGravityDirection() == GRAVITY_DOWN) gravityText << "Gravity: DOWN";
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
	m_BackgroundA.free();
	m_BackgroundB.free();
	m_MidgroundA.free();
	m_MidgroundB.free();

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