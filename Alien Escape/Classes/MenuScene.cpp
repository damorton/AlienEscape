/*
MenuScene.cpp

Menu Scene is the title screen for the game and contains the title label and
start game button. The Menu Scene has an update loop that will process inputs
and render textures/Sprites

@author	David Morton K00179391
@date	13.4.15
*/
//Includes
#include "MenuScene.h"
#include "GameScene.h"
#include "WorldManager.h"
#include "Timer.h"
#include "Label.h"

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
	printf("MenuScene: Destroyed\n");
	this->cleanup();
}

bool MenuScene::init()
{
	bool success = true;
	thisSceneState = RUNNING;
	m_pWorldManager = WorldManager::getInstance();
	
	printf("MenuScene: Initialized\n");
	return success;
}

bool MenuScene::loadMedia()
{
	printf("MenuScene: Loading Media\n");
	bool success = true;

	//Load Fonts from XML file
	m_Font = TTF_OpenFont(m_pWorldManager->readDAO("GameFont").c_str(), 38);
	if (m_Font == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}

	//Load background texture from XML file
	//if (!m_Background.loadFromFile("Resources/Backgrounds/MenuBackground.png"))
	if (!m_Background.loadFromFile(m_pWorldManager->readDAO("MenuSceneBackground")))
	{
		printf("Failed to load background texture!\n");
		success = false;
	}

	//Set text color as White
	//m_TextColor = COLOR_WHITE;
	m_TextColor = {255, 0, 89, 255};

	//Create title label
	m_Title = new Label(m_pWorldManager->readDAO("GameName"), m_TextColor, m_Font);
	m_Title->setPosition(SCREEN_WIDTH * .5 - m_Title->getSprite()->getWidth() / 2, SCREEN_HEIGHT * .05);

	//Create start button	
	m_StartButton = new Label(m_pWorldManager->readDAO("MenuSceneStartLabel"), m_TextColor, m_Font);
	m_StartButton->setPosition(SCREEN_WIDTH * .5 - m_StartButton->getSprite()->getWidth() / 2, SCREEN_HEIGHT * .85);

	return success;
}

void MenuScene::startGame()
{
	// Run GameScene
	GameScene* gameScene = new GameScene();
	WorldManager::getInstance()->runWithScene(gameScene);
}

bool MenuScene::run()
{		
	//Initialize update loop
	SDL_Event e;	
	int lifetimeofscene = 200;
	Timer capTimer;
	int countedFrames = 0;

	while (thisSceneState != DESTROY)
	{
		capTimer.start();
		//printf("MenuScene: Running update...\n");

		// -------------------- INPUT --------------------		
		capTimer.start();
		while (SDL_PollEvent(&e) != 0)
		{
			//If x button clicked
			if (e.type == SDL_QUIT)
			{
				thisSceneState = DESTROY;
			}

			//If a key was pressed
			if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
			{
				//Space key to start new game; Start Button now implmeneted
				if (e.key.keysym.sym == SDLK_SPACE)
				{
					/*
					startGame();
					return 0;
					*/
				}
			}

			// Mouse events
			//If mouse event happened
			if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
			{
				//Get mouse position
				int x, y;
				SDL_GetMouseState(&x, &y);

				//Check if mouse is in button
				bool inside = true;

				//Mouse is left of the button
				if (x < m_StartButton->getPositionX())
				{
					inside = false;
				}
				//Mouse is right of the button
				else if (x > m_StartButton->getPositionX() + m_StartButton->getSprite()->getWidth())
				{
					inside = false;
				}
				//Mouse above the button
				else if (y < m_StartButton->getPositionY())
				{
					inside = false;
				}
				//Mouse below the button
				else if (y > m_StartButton->getPositionY() + m_StartButton->getSprite()->getHeight())
				{
					inside = false;
				}

				//Mouse is outside button
				if (!inside)
				{

				}
				//Mouse is inside button
				else
				{
					//Set mouse over sprite
					switch (e.type)
					{
					case SDL_MOUSEMOTION:
						//mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
						break;
					case SDL_MOUSEBUTTONDOWN:
						// Run GameScene
						startGame();
						return 0;
						break;
					case SDL_MOUSEBUTTONUP:
						//mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
						break;
					}
				}

			}

		}

		// -------------------- LOGIC --------------------


		// -------------------- RENDER --------------------
		SDL_SetRenderDrawColor(m_pWorldManager->getRenderer(), 0x00, 0x00, 0x00, 0xFF);
		SDL_RenderClear(m_pWorldManager->getRenderer());

		//Render background
		m_Background.render(0, 0);

		//Render Title and Start Button
		m_Title->render();
		m_StartButton->render();
		
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
	m_pWorldManager = nullptr;

	//Free loaded images
	m_Background.free();	
	
	//Delete game objects
	delete m_StartButton;
	m_StartButton = nullptr;
	delete m_Title;
	m_Title = nullptr;
		
	//Free global font
	TTF_CloseFont(m_Font);
	m_Font = nullptr;
	printf("MenuScene: Destroying Assets\n");
}