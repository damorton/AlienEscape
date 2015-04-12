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

	Label* m_PauseButton;

	TTF_Font* m_Font = nullptr;
	SDL_Color m_TextColor;
};