#include "MenuScene.h"
#include "WorldManager.h"

int main(int argc, char* args[])
{	
	MenuScene* menuScene = new MenuScene();
	WorldManager::getInstance()->runWithScene(menuScene);
	return 0;
}