#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <memory>

class Player;
class Enemy;

class GameManager
{
public:	
	GameManager(){ this->init(); }; 
	~GameManager(){ this->cleanUp(); }; 
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
		
	// Player
	std::shared_ptr<Player> m_pPlayer;
};

#endif