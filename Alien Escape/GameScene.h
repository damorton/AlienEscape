#ifndef GAMESCENE_H_
#define GAMESCENE_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <sstream>
#include <memory>

#include "Scene.h"
#include "Sprite.h"

class Player;
class WorldManager; 

class GameScene : public Scene
{
public:	
	GameScene();
	virtual ~GameScene();
	virtual bool init();
	virtual bool run();
	virtual void cleanup();	

	void update(); 
	bool loadMedia();	
	void renderDebug();
	void initDebug();
private:			
	SDL_Window* m_Window = NULL;
	SDL_Renderer* m_Renderer = NULL;			
	TTF_Font* m_Font = NULL;	
	WorldManager* m_pWorldManager;
	//std::shared_ptr<Player> m_pPlayer;
	Player* m_pPlayer = NULL;
	SDL_Color textColor;
	Sprite m_FPSTextTexture;
	Sprite m_BackgroundA;
	Sprite m_BackgroundB;
	Sprite m_MidgroundA;
	Sprite m_MidgroundB;
	float avgFPS;	
	std::stringstream fpsText;
	Sprite m_GravityTextTexture;
	std::stringstream gravityText;
	Sprite m_DistanceTextTexture;	
	std::stringstream distanceText;
	// reminder: release resources in cleanup
};

#endif