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
	int getGravityDirection(){ return gravityDirection; }
	SDL_RendererFlip getRendererFlip(){ return m_RendererFlip; };
	void setRenderer(SDL_Renderer* renderer){ m_pRenderer = renderer; };
private:
	WorldManager(){ this->init(); };
	~WorldManager(){ this->cleanUp(); };
	static WorldManager* m_Instance; 
	SDL_Renderer* m_pRenderer;	
	Gravity gravityDirection;
	SDL_RendererFlip m_RendererFlip;
	// reminder: release resources in cleanup
};
#endif