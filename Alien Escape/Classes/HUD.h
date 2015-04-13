/*
HUD.h

Game scene runs the main Game Loop and handles the creation and destruction
of all Sprite in game. The Game Scene contains the HUD and controls frame rate,
input processing, rendering and all timing related tasks.

@author	David Morton K00179391
@date	13.4.15
*/
#include <sstream>
#include "Definitions.h"
#include "Sprite.h"

class WorldManager;
class Label;

class HUD
{
public:
	HUD();
	virtual ~HUD();
	void render();
	bool init();
	bool loadMedia();
	void cleanup();
	void handleEvent(SDL_Event& e);
private:
	WorldManager* m_pWorldManager;
	
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

	Label* m_PauseButton;

	TTF_Font* m_Font = nullptr;
	SDL_Color m_TextColor;	
};