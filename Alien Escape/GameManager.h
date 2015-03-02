#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <memory>

class Player;
class Enemy;
class Boss;

class GameManager
{
public:	
	GameManager(){ this->init(); }; 
	~GameManager(){ this->cleanUp(); }; 
	bool init(); 	
	bool start();
	bool update(); 
	bool loadMedia();
	void cleanUp(); 		
private:	
	
	std::vector<std::shared_ptr<Enemy>> m_pvEnemies; // Enemy vector
	std::shared_ptr<Boss> m_pBoss; // Boss	
	
	//The window we'll be rendering to
	SDL_Window* m_Window = NULL;

	//The window renderer
	SDL_Renderer* m_Renderer = NULL;
		
	//LTexture gDotTexture;
	std::shared_ptr<Player> m_pPlayer; // Player
};

#endif