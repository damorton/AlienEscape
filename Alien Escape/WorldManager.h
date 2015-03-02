#ifndef WORLDMANAGER_H_
#define WORLDMANAGER_H_

#include <SDL.h>

class WorldManager
{
public:
	static WorldManager* getInstance();
	bool init();	
	void cleanUp(); 
	void setRenderer(SDL_Renderer* renderer){ m_pRenderer = renderer; };
	SDL_Renderer* getRenderer(){ return m_pRenderer; };
private:
	static WorldManager* m_Instance; 
	WorldManager(){ this->init(); }; 
	~WorldManager(){ this->cleanUp(); }; 		
	SDL_Renderer* m_pRenderer;
};
#endif