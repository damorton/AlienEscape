#ifndef GAMESCENE_H_
#define GAMESCENE_H_

#include <sstream>
#include <memory>

#include "Scene.h"
#include "Sprite.h"

class Player;
class Enemy;
class WorldManager; 
class HUD;
class Timer;

class GameScene : public Scene
{
public:	
	GameScene();
	virtual ~GameScene();
	virtual bool init();
	virtual bool run();
	virtual void cleanup();	
	virtual void pause();
	bool update();
	bool loadMedia();	

	float getAverageFPS(){ return m_fAverageFPS; };
	
private:			
	WorldManager* m_pWorldManager;
	TTF_Font* m_Font = nullptr;

	//std::shared_ptr<Player> m_pPlayer;
	Player* m_pPlayer = nullptr;
	Enemy* m_pEnemyAlien = nullptr;

	HUD* m_pHUD;

	SDL_Color m_TextColor;

	Timer* deltaTimer;
	
	Sprite m_BackgroundA;
	Sprite m_BackgroundB;
	Sprite m_MidgroundA;
	Sprite m_MidgroundB;
		
	float m_fAverageFPS;
	
	Sprite m_FPSTextTexture;
	std::stringstream fpsText;
	Sprite m_GravityTextTexture;
	std::stringstream gravityText;
	Sprite m_DistanceTextTexture;	
	std::stringstream distanceText;
	// reminder: release resources in cleanup
};

#endif