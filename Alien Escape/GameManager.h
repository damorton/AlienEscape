#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "Sprite.h"
#include <sstream>

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
	void renderDebug();
	void initDebug();
private:			
	SDL_Window* m_Window = NULL;
	SDL_Renderer* m_Renderer = NULL;			
	TTF_Font* m_Font = NULL;	
	Player* m_pPlayer;

	SDL_Color textColor;

	Sprite m_FPSTextTexture;
	float avgFPS;	
	std::stringstream fpsText;

	Sprite m_GravityTextTexture;
	std::stringstream gravityText;

	Sprite m_DistanceTextTexture;	
	std::stringstream distanceText;
};

#endif