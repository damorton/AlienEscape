/*
MenuScene.h

Menu Scene is the title screen for the game and contains the title label and
start game button. The Menu Scene has an update loop that will process inputs
and render textures/Sprites

@author	David Morton K00179391
@date	13.4.15
*/
#ifndef MENUSCENE_H
#define MENUSCENE_H

//Includes
#include <sstream>
#include <memory>
#include "Scene.h"
#include "Definitions.h"
#include "Sprite.h"

//Forward Declarations
class WorldManager; 
class Label;

class MenuScene : public  Scene
{
public:
	MenuScene();
	virtual ~MenuScene();

	//Implement Scene functions
	bool init();
	bool run();
	void cleanup();
	void pause(){};
	bool loadMedia();

	//Create and run new game scene
	void startGame();
	
private:
	WorldManager* m_pWorldManager;
	TTF_Font* m_Font = nullptr;
	SDL_Color m_TextColor;

	//Background
	Sprite m_Background;
	
	//Labels
	Label* m_StartButton;	
	Label* m_Title;
	//std::shared_ptr<Label> m_spStartButton;
};

#endif