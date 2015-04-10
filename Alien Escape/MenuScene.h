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
	virtual bool init();
	virtual bool run();
	virtual void cleanup();
	virtual bool loadMedia();
	virtual void startGame();
	
private:
	WorldManager* m_pWorldManager;
	TTF_Font* m_Font = nullptr;
	Sprite m_Background;
	SDL_Color m_TextColor;

	Label* m_StartButton;	
};



#endif