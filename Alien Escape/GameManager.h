#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <memory>
#include "Sprite.h"

class Player;

//Walking animation
const int WALKING_ANIMATION_FRAMES = 4;

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
		
	//The window we'll be rendering to
	SDL_Window* m_Window = NULL;

	//The window renderer
	SDL_Renderer* m_Renderer = NULL;
		
	//Sprite m_pPlayer;

	// Player
	std::shared_ptr<Player> m_pPlayer;

	SDL_Rect gSpriteClips[WALKING_ANIMATION_FRAMES];
};

#endif