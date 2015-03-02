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


void GameManager::update()
{	
	//Main loop flag
	bool quit = false;

	//Event handler
	SDL_Event e;

	//Current animation frame
	int frame = 0;

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
		}

		//Clear screen
		SDL_SetRenderDrawColor(WorldManager::getInstance()->getRenderer(), 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(WorldManager::getInstance()->getRenderer());

		//Render current frame
		SDL_Rect* currentClip = &gSpriteClips[frame / 4];
		playerSpriteSheet.render((SCREEN_WIDTH - currentClip->w) / 2, (SCREEN_HEIGHT - currentClip->h) / 2, currentClip);

		//Update screen
		SDL_RenderPresent(WorldManager::getInstance()->getRenderer());

		//Go to next frame
		++frame;

		//Cycle animation
		if (frame / 4 >= WALKING_ANIMATION_FRAMES)
		{
			frame = 0;
		}
	}
}

bool GameManager::loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load sprite sheet texture
	if (!playerSpriteSheet.loadFromFile("Sprites/foo.png"))
	{
		printf("Failed to load walking animation texture!\n");
		success = false;
	}
	else
	{
		//Set sprite clips
		gSpriteClips[0].x = 0;
		gSpriteClips[0].y = 0;
		gSpriteClips[0].w = 32;
		gSpriteClips[0].h = 103;

		gSpriteClips[1].x = 32;
		gSpriteClips[1].y = 0;
		gSpriteClips[1].w = 32;
		gSpriteClips[1].h = 103;

		gSpriteClips[2].x = 64;
		gSpriteClips[2].y = 0;
		gSpriteClips[2].w = 32;
		gSpriteClips[2].h = 103;

		gSpriteClips[3].x = 96;
		gSpriteClips[3].y = 0;
		gSpriteClips[3].w = 32;
		gSpriteClips[3].h = 103;
	}

	return success;
}

void GameManager::cleanUp()
{
	//Free loaded images
	playerSpriteSheet.free();

	//Destroy window	
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
	m_Renderer = NULL;
	m_Window = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}