#include "GameManager.h"
#include "Definitions.h"
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
			//Create renderer for window
			m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);
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

	return success;
}

bool GameManager::update()
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
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//The dot that will be moving around on the screen
			//Dot dot;
			//Player player;

			//Keeps track of time between steps
			Timer stepTimer;

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

					//Handle input for the dot
					//dot.handleEvent(e);
					//player.handleEvent(e);
				}

				//Calculate time step
				float timeStep = stepTimer.getTicks() / 1000.f;

				//Move for time step
				//dot.move(timeStep);
				//player.move(timeStep);

				//Restart step timer
				stepTimer.start();

				//Clear screen
				SDL_SetRenderDrawColor(m_Renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				SDL_RenderClear(m_Renderer);

				//Render dot
				//dot.render();
				//player.render();

				//Update screen
				SDL_RenderPresent(m_Renderer);
			}
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

	//Load dot texture
	//if (!gDotTexture.loadFromFile("44_frame_independent_movement/dot.bmp"))
	if (!m_pPlayer.loadFromFile("44_frame_independent_movement/dot.bmp"))
	{
		printf("Failed to load dot texture!\n");
		success = false;
	}

	return success;
}

void GameManager::cleanUp()
{
	//Free loaded images
	//gDotTexture.free();
	m_pPlayer.free();

	//Destroy window	
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
	m_Window = NULL;
	m_Renderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}