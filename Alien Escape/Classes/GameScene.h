/*
GameScene.h

Game scene runs the main Game Loop and handles the creation and destruction
of all Sprite in game. The Game Scene contains the HUD and controls frame rate,
input processing, rendering and all timing related tasks.

@author	David Morton K00179391
@date	13.4.15
*/
#ifndef GAMESCENE_H_
#define GAMESCENE_H_

//Includes
#include <sstream>
#include <memory>
#include "Scene.h"
#include "Sprite.h"

//Forward declarations
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

	//Implement Scene functions
	bool init();
	bool run();
	void cleanup();	
	void pause();
	
	/*
		Game Loop 

		@return bool returning control and exiting loop
	*/
	bool update();

	/*
		Load all media used in the Game Scene

		@return bool success true is all media loaded without problems
	*/
	bool loadMedia();	

	/*
		Return average FPS used by HUD
	*/
	float getAverageFPS(){ return m_fAverageFPS; };
	
private:			
	WorldManager* m_pWorldManager;
	TTF_Font* m_Font = nullptr;
	//std::shared_ptr<Player> m_pPlayer; // implement shared pointers if theres enough time
	Player* m_pPlayer = nullptr;
	Enemy* m_pEnemyAlien = nullptr;
	//Enemy * m_pEnemyAlien2 = nullptr;
	HUD* m_pHUD = nullptr;
	SDL_Color m_TextColor;
	Timer* deltaTimer;
	Timer* m_pGravityTimer;	
	
	//Background Sprites for parallax
	Sprite m_BackgroundA;
	Sprite m_BackgroundB;
	Sprite m_MidgroundA;
	Sprite m_MidgroundB;
		
	float m_fAverageFPS;		
	// reminder: release resources in cleanup
};

#endif