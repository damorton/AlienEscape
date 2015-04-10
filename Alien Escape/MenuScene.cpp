#include "MenuScene.h"
#include "GameScene.h"
#include "WorldManager.h"
#include "Timer.h"

MenuScene::MenuScene()
{	
	if (!init())
	{
		printf("Failed to initialize Game Scene!\n");
	}
	else
	{
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}			
	}	
}

MenuScene::~MenuScene()
{
	this->cleanup();
}

bool MenuScene::init()
{
	bool success = true;
	thisSceneState = RUNNING;
	m_pWorldManager = WorldManager::getInstance();

	//Set text color as White
	m_TextColor = COLOR_WHITE;

	printf("MenuScene: Initialized\n");
	return success;
}

bool MenuScene::loadMedia()
{
	printf("MenuScene: Loading Media\n");
	bool success = true;

	// Fonts
	m_Font = TTF_OpenFont("Fonts/go3v2.ttf", 28);
	if (m_Font == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}

	//Load background texture
	if (!m_Background.loadFromFile("Backgrounds/MenuBackground.png"))
	{
		printf("Failed to load background texture!\n");
		success = false;
	}
	return success;
}


bool MenuScene::run()
{		
	SDL_Event e;

	
	int lifetimeofscene = 200;
	Timer capTimer;
	int countedFrames = 0;

	while (thisSceneState == RUNNING)
	{	
		capTimer.start();
		//printf("MenuScene: Running update...\n");

		// -------------------- INPUT --------------------		
		capTimer.start();
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				thisSceneState = DESTROY;
			}

			//If a key was pressed
			if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
			{
				if (e.key.keysym.sym == SDLK_SPACE)
				{	
					// Run GameScene
					GameScene* gameScene = new GameScene();
					WorldManager::getInstance()->runWithScene(gameScene);	
					return 0; // Exit game
				}
			}
					
		}

		// -------------------- LOGIC --------------------
				

		// -------------------- RENDER --------------------
		SDL_SetRenderDrawColor(m_pWorldManager->getRenderer(), 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(m_pWorldManager->getRenderer());

		// Render background A
		m_Background.render(0, 0);


		// Start Game Label
		m_strStartGameLabel.str("");			
		m_strStartGameLabel << "Press Enter";
		if (!m_StartLabel.loadFromRenderedText(m_strStartGameLabel.str().c_str(), m_TextColor, m_Font))
		{
			printf("Unable to render FPS texture!\n");
		}
		m_StartLabel.render(SCREEN_WIDTH * .5 - m_StartLabel.getWidth() * .5, SCREEN_HEIGHT * .75);
				
		SDL_RenderPresent(m_pWorldManager->getRenderer());

		// -------------------- DELAY --------------------
		++countedFrames;
		int frameTicks = capTimer.getTicks();
		if (frameTicks < SCREEN_TICK_PER_FRAME)
		{
			SDL_Delay(SCREEN_TICK_PER_FRAME - frameTicks);
		}
	}	
	return 0;
}

void MenuScene::cleanup()
{
	printf("MenuScene: Destroying Assets\n");
	//Free loaded images
	m_StartLabel.free();		
	m_Background.free();		
		
	//Free global font
	TTF_CloseFont(m_Font);
	m_Font = nullptr;
}