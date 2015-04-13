#ifndef MENUSCENE_H
#define MENUSCENE_H

#include <sstream>
#include "Scene.h"
#include "Definitions.h"
#include "Sprite.h"

class WorldManager; 
class Label;

class MenuScene : public  Scene
{
public:
	MenuScene();
	virtual ~MenuScene();
	bool init();
	bool run();
	void cleanup();
	void pause(){};
	bool loadMedia();
	void startGame();
	
private:
	WorldManager* m_pWorldManager;
	TTF_Font* m_Font = nullptr;
	Sprite m_Background;
	SDL_Color m_TextColor;
	Label* m_StartButton;	
	Label* m_Title;
};



#endif