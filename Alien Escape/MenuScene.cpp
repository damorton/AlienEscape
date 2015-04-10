#include "MenuScene.h"
#include "GameScene.h"
#include "WorldManager.h"

MenuScene::MenuScene()
{
	if (!Scene::init())
	{
		printf("Failed to initialize Scene!\n");		
	}
	else
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
}

MenuScene::~MenuScene()
{
	this->cleanup();
}

bool MenuScene::init()
{
	bool success = true;
		
	printf("MenuScene: initialized\n");
	return success;
}

bool MenuScene::loadMedia()
{
	bool success = true;
	
	return success;
}


bool MenuScene::run()
{		
	thisSceneState = RUNNING;
	int lifetimeofscene = 200;

	while (thisSceneState == RUNNING)
	{	
		printf("MenuScene: running...\n");
		lifetimeofscene--;
		if (lifetimeofscene < 1)
			thisSceneState = DESTROY;
	}
	GameScene* gameScene = new GameScene();
	WorldManager::getInstance()->runWithScene(gameScene);
	return 0;
}

void MenuScene::cleanup()
{
	printf("MenuScene: destroying assets\n");
}