#include "Scene.h"
#include <iostream>

Scene::Scene()
{
	if (!init())
	{
		std::cout << "Scene: Failed to initialize Scene\n" << std::endl;
	}
	initCompleted = false;	
}

bool Scene::init()
{
	bool success = true;
	thisSceneState = RUNNING;
	std::cout << "Scene: Scene Initializing" << std::endl;
	std::cout << "Scene: Loading Textures" << std::endl;	
	return success;
}

bool Scene::run()
{
	if (!initCompleted)
	{
		init();
	}
	
	while (thisSceneState == RUNNING)
	{
		std::cout << "Update world" << std::endl;
		std::cout << "Checking Collisions" << std::endl;
		std::cout << "Handle Input" << std::endl;
	}
	return 0;
}

void Scene::cleanup()
{
	std::cout << "Scene: Destroying Assets" << std::endl;
}


Scene::~Scene(){
	cleanup();
	std::cout << "Scene: Shutting down Scene" << std::endl;
}