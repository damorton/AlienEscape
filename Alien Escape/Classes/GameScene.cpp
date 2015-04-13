/*
GameScene.h

Game scene runs the main Game Loop and handles the creation and destruction
of all Sprite in game. The Game Scene contains the HUD and controls frame rate,
input processing, rendering and all timing related tasks.

@author	David Morton K00179391
@date	13.4.15
*/
#include "GameScene.h"
#include "MenuScene.h"
#include "WorldManager.h"
#include "Definitions.h"
#include "Player.h"
#include "Enemy.h"
#include "Timer.h"
#include "HUD.h"

GameScene::GameScene()
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

GameScene::~GameScene()
{
	this->cleanup();
}

bool GameScene::init()
{
	bool success = true;
	thisSceneState = RUNNING;
	m_pWorldManager = WorldManager::getInstance();	
	m_pWorldManager->resetGame();	
	m_TextColor = COLOR_WHITE;
		
	m_pPlayer = new Player();
	m_pWorldManager->registerPlayer(m_pPlayer);	
	m_pEnemyAlien = new Enemy();
	m_pEnemyAlien->setPositionX(SCREEN_WIDTH * 1.5);
	m_pWorldManager->registerGameNode((Node*)m_pEnemyAlien);
	//m_pEnemyAlien2 = new Enemy();
	//m_pWorldManager->registerGameNode((Node*)m_pEnemyAlien2);
	m_pHUD = new HUD();
	m_pGravityTimer = new Timer();
	
	//std::shared_ptr<Player> m_pPlayer(new Player());
	printf("GameScene: Initialized\n");
	return success;
}

bool GameScene::run()
{
	// run game loop
	this->update();
	return 0;
}

bool GameScene::loadMedia()
{
	printf("GameScene: Loading Media\n");
	bool success = true;

	// Sprites
	if (!m_pPlayer->getSprite()->loadFromFile(m_pWorldManager->readDAO("GameScenePlayer")))
	{
		printf("Failed to load walking animation texture!\n");
		success = false;
	}	

	// Enemy
	if (!m_pEnemyAlien->getSprite()->loadFromFile(m_pWorldManager->readDAO("GameSceneEnemyAlien")))
	{
		printf("Failed to load walking animation texture!\n");
		success = false;
	}

	/*
	if (!m_pEnemyAlien2->getSprite()->loadFromFile(m_pWorldManager->readDAO("GameSceneEnemyAlien")))
	{
		printf("Failed to load walking animation texture!\n");
		success = false;
	}
	*/


	// Fonts
	m_Font = TTF_OpenFont(m_pWorldManager->readDAO("GameFont").c_str(), 28);
	if (m_Font == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}	

	//Load background texture
	if (!m_BackgroundA.loadFromFile(m_pWorldManager->readDAO("GameSceneBackgroundA")))
	{
		printf("Failed to load background texture!\n");
		success = false;
	}
	if (!m_BackgroundB.loadFromFile(m_pWorldManager->readDAO("GameSceneBackgroundB")))
	{
		printf("Failed to load background texture!\n");
		success = false;
	}
	if (!m_MidgroundA.loadFromFile(m_pWorldManager->readDAO("GameSceneMidgroundA")))
	{
		printf("Failed to load background texture!\n");
		success = false;
	}
	if (!m_MidgroundB.loadFromFile(m_pWorldManager->readDAO("GameSceneMidgroundB")))
	{
		printf("Failed to load background texture!\n");
		success = false;
	}

	return success;
}

void GameScene::pause()
{
	if (thisSceneState == PAUSED)
	{
		thisSceneState = RUNNING;
		deltaTimer->unpause();
	}
	else
	{
		thisSceneState = PAUSED;
		deltaTimer->pause();
	}	
}

bool GameScene::update()
{	
	
	SDL_Event e;
	float backgroundAscrollingOffset = 0;
	float backgroundBscrollingOffset = SCREEN_WIDTH;
	float midgroundAscrollingOffset = 0;
	float midgroundBscrollingOffset = SCREEN_WIDTH;
	Timer fpsTimer;
	Timer capTimer;
	deltaTimer = new Timer();
	fpsTimer.start();	
	int countedFrames = 0;	
	m_pGravityTimer->start();

	// -------------------- GAME LOOP START --------------------
	while (thisSceneState != DESTROY)
	{		
		capTimer.start();


		// -------------------- INPUT --------------------	
		while (SDL_PollEvent(&e) != 0)
		{	
			// Game World Input
			if (e.type == SDL_QUIT)
			{
				thisSceneState = DESTROY;
			}			
			
			// Game object input
			if (!m_pWorldManager->getInstance()->getRunningScene()->isPaused())
			{
				// Characters
				m_pPlayer->handleEvent(e);
				m_pEnemyAlien->handleEvent(e);
				//m_pEnemyAlien2->handleEvent(e);
			}

			m_pHUD->handleEvent(e);
			
		}	


		// If the game is not paused
		if (!m_pWorldManager->getInstance()->getRunningScene()->isPaused())
		{

			// -------------------- LOGIC --------------------

			m_fAverageFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);

			if (m_fAverageFPS > 2000000)
			{
				m_fAverageFPS = 0;
			}
			m_pWorldManager->setAverageFPS(m_fAverageFPS);

			float timeStep = deltaTimer->getTicks() / 1000.f;
			m_pPlayer->move(timeStep);
			m_pEnemyAlien->move(timeStep);
			//m_pEnemyAlien2->move(timeStep);
			deltaTimer->start();
		
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

			// Gravity controls
			if (m_pGravityTimer->getTicks() > 3000)
			{	
				if (m_pEnemyAlien->getSprite()->getPositionX() > SCREEN_WIDTH * .60)
				{
					m_pWorldManager->flipGravity();
				}				
				m_pGravityTimer->stop();
				m_pGravityTimer->start();				
			}

			// Collisions
			if (m_pWorldManager->checkCollisions())
			{				
				return 0;
			}
			/*
			if (m_pPlayer->getSprite()->checkCollision(m_pEnemyAlien->getSprite()->getBoundBox()) && m_pEnemyAlien->getState() == Character::ALIVE)
			{
				printf("Collision Detected: Player and Enemy\n");
				m_pPlayer->setState(Character::DEAD);
				m_pEnemyAlien->setState(Character::DEAD);
				
				// Game over
				MenuScene* menuScene = new MenuScene();
				WorldManager::getInstance()->runWithScene(menuScene);
				return 0;
				
			}*/
			
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

			m_pPlayer->render();
			m_pEnemyAlien->render();
			//m_pEnemyAlien2->render();
			m_pHUD->render();
			SDL_RenderPresent(m_pWorldManager->getRenderer());
		}

		
		// -------------------- DELAY --------------------
		++countedFrames;
		int frameTicks = capTimer.getTicks();
		if (frameTicks < SCREEN_TICK_PER_FRAME)
		{
			SDL_Delay(SCREEN_TICK_PER_FRAME - frameTicks);
		}
				
	}
	// -------------------- GAME LOOP END --------------------
	return 0;
}

void GameScene::cleanup()
{
	printf("GameScene: Destroying Assets\n");
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
	m_pPlayer = nullptr;

	delete m_pEnemyAlien;
	m_pEnemyAlien = nullptr;

	//delete m_pEnemyAlien2;
	//m_pEnemyAlien2 = nullptr;


	delete deltaTimer;
	deltaTimer = nullptr;

	delete m_pHUD;
	m_pHUD = nullptr;

	//Free global font
	TTF_CloseFont(m_Font);
	m_Font = nullptr;	
}