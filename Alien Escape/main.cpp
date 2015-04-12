#include "Classes/MenuScene.h"
#include "Classes/WorldManager.h"

int main(int argc, char* args[])
{	
	MenuScene* menuScene = new MenuScene();
	WorldManager::getInstance()->runWithScene(menuScene);
	return 0;
}