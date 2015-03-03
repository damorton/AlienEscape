#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include <SDL.h>
#include <SDL_image.h>
#include "Sprite.h"

class Player;

class GameManager
{
public:	
	GameManager(){}
	bool init();
	bool start();
	void update(); 
	bool loadMedia();
	void cleanUp(); 			
private:			
	SDL_Window* m_Window = NULL;
	SDL_Renderer* m_Renderer = NULL;		
	Player* m_pPlayer;	
};

#endif