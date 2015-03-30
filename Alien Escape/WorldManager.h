#ifndef WORLDMANAGER_H_
#define WORLDMANAGER_H_

#include <SDL.h>
#include "Definitions.h"

class WorldManager
{
public:
	static WorldManager* getInstance();
	bool init();	
	void cleanUp(); 	
	void flipGravity();	
	SDL_Renderer* getRenderer(){ return m_pRenderer; };
	int getGravityDirection(){ return m_eGravitationalPull; }
	SDL_RendererFlip getRendererFlip(){ return m_RendererFlip; };
	void setRenderer(SDL_Renderer* renderer){ m_pRenderer = renderer; };

	float getGameWorldSpeed(){ return m_nGameWorldSpeed; };
	void setGameWorldSpeed(float speed){ m_nGameWorldSpeed = speed; };
	void increaseGameWorldSpeed(){ m_nGameWorldSpeed += SPEED_INC; };
private:
	WorldManager(){ this->init(); };
	~WorldManager(){ this->cleanUp(); };
	static WorldManager* m_Instance; 
	SDL_Renderer* m_pRenderer;	
	Gravity m_eGravitationalPull;
	SDL_RendererFlip m_RendererFlip;
	float m_nGameWorldSpeed;
	// reminder: release resources in cleanup
};
#endif