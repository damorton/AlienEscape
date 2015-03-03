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
		m_Window = SDL_CreateWindow("Alien Escape", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
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

				//Initialize SDL_ttf
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

	//Open the font
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
	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;
	
	this->initDebug();

	//The frames per second timer
	Timer fpsTimer;

	//The frames per second cap timer
	Timer capTimer;
	
	//Start counting frames per second
	int countedFrames = 0;
	fpsTimer.start();

	Timer deltaTimer;

	//While application is running
	while (!quit)
	{
		//Start cap Timer
		capTimer.start();

		// -------------------- INPUT --------------------
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

		//Calculate and correct fps
		avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
		if (avgFPS > 2000000)
		{
			avgFPS = 0;
		}
		
		//Calculate time step
		float timeStep = deltaTimer.getTicks() / 1000.f;
		
		// -------------------- LOGIC --------------------
		// Move for timestep
		m_pPlayer->move(timeStep);

		// Restart timer
		deltaTimer.start();

		// -------------------- RENDER --------------------
		//Clear screen
		SDL_SetRenderDrawColor(WorldManager::getInstance()->getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(WorldManager::getInstance()->getRenderer());
		
		this->renderDebug();		

		// Render the player
		m_pPlayer->render();

		//Update screen
		SDL_RenderPresent(WorldManager::getInstance()->getRenderer());

		++countedFrames;

		//If frame finished early
		int frameTicks = capTimer.getTicks();
		if (frameTicks < SCREEN_TICK_PER_FRAME)
		{
			//Wait remaining time
			SDL_Delay(SCREEN_TICK_PER_FRAME - frameTicks);
		}
	}
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