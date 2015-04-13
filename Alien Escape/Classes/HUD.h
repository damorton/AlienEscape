/*
HUD.h

Heads Up Display updates the player and game stats like distance
travelled and booster status. The HUD contains a pause button allowing the
player to pause the game during a session.

@author	David Morton K00179391
@date	13.4.15
*/
//Includes
#include <sstream>
#include "Definitions.h"
#include "Scene.h"
#include "Sprite.h"

//Forward Declarations
class WorldManager;
class Label;

class HUD : public Scene
{
public:
	HUD();
	virtual ~HUD();

	//Implement Scene functions
	void render();
	bool init();
	bool run();
	void pause(){};
	bool loadMedia();
	void cleanup();

	//Handle input events
	void handleEvent(SDL_Event& e);
private:
	WorldManager* m_pWorldManager;
	
	//Display game status to the player
	Sprite m_FPSTextTexture;
	std::stringstream fpsText;
	Sprite m_GameSpeedTextTexture;
	std::stringstream m_ssGameSpeedText;
	Sprite m_GravityTextTexture;
	std::stringstream gravityText;
	Sprite m_DistanceTextTexture;
	std::stringstream distanceText;
	Sprite m_BoostTexture;
	std::stringstream boosterText;
	Sprite m_LivesTexture;
	std::stringstream livesText;

	//Pause button functionality
	Label* m_PauseButton;

	//Config
	TTF_Font* m_Font = nullptr;
	SDL_Color m_TextColor;	
};