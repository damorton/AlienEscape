#ifndef WORLDMANAGER_H_
#define WORLDMANAGER_H_

#include <SDL.h>
#include "Definitions.h"
#include "Scene.h"

#include "Player.h"

class WorldManager
{
public:
	static WorldManager* getInstance();
	bool init();
	void runWithScene(Scene* scene);
	void exit();
	void cleanUp();
	void flipGravity();
	SDL_Renderer* getRenderer(){ return m_Renderer; };
	int getGravityDirection(){ return m_eGravitationalPull; }
	SDL_RendererFlip getRendererFlip(){ return m_RendererFlip; };
	float getGameWorldSpeed(){ return m_nGameWorldSpeed; };
	void setGameWorldSpeed(float speed){ m_nGameWorldSpeed = speed; };
	void increaseGameWorldSpeed(){ m_nGameWorldSpeed += SPEED_INC; };

	Scene* getRunningScene(){ return currentRunningScene; };

	Player* getPlayer(){ return m_pPlayer; };
	void registerPlayer(Player* player){ m_pPlayer = player; };

	float getAverageFPS(){ return m_fAverageFPS; };
	void setAverageFPS(float fps){ m_fAverageFPS = fps; };

private:
	WorldManager();
	~WorldManager();
	static WorldManager* m_Instance; 

	SDL_Window* m_Window = NULL;
	SDL_Renderer* m_Renderer = NULL;

	Gravity m_eGravitationalPull;
	SDL_RendererFlip m_RendererFlip;
	float m_nGameWorldSpeed;

	Scene* currentRunningScene;

	bool m_bIsPaused;
	float m_fAverageFPS;

	Player* m_pPlayer;
	// reminder: release resources in cleanup
};
#endif