#include "HUD.h"
#include "WorldManager.h"
#include "GameScene.h"
HUD::HUD()
{
	if (!init())
	{
		printf("Failed to initialize Game Scene!\n");
	}
	else
	{
		if (!loadMedia())
		{
			printf("Failed to load media!\n");
		}
	}
}

HUD::~HUD()
{
}

bool HUD::init()
{
	bool success = true;
	m_pWorldManager = WorldManager::getInstance();
	//Set text color as White
	m_TextColor = COLOR_WHITE;
	return success;
}

bool HUD::loadMedia()
{	
	bool success = true;

	// Fonts
	m_Font = TTF_OpenFont("Fonts/go3v2.ttf", 28);
	if (m_Font == NULL)
	{
		printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	
	return success;
}

void HUD::render()
{
	// Game speed
	m_ssGameSpeedText.str("");
	m_ssGameSpeedText << "Speed : " << m_pWorldManager->getGameWorldSpeed();
	if (!m_GameSpeedTextTexture.loadFromRenderedText(m_ssGameSpeedText.str().c_str(), m_TextColor, m_Font))
	{
		printf("Unable to render FPS texture!\n");
	}
	m_GameSpeedTextTexture.render(PADDING, SCREEN_HEIGHT - PADDING - m_FPSTextTexture.getHeight() - m_GameSpeedTextTexture.getHeight());

	//Set text to be rendered
	fpsText.str("");
	fpsText << "FPS: " << m_pWorldManager->getAverageFPS();
	if (!m_FPSTextTexture.loadFromRenderedText(fpsText.str().c_str(), m_TextColor, m_Font))
	{
		printf("Unable to render FPS texture!\n");
	}
	m_FPSTextTexture.render(PADDING, SCREEN_HEIGHT - PADDING - m_FPSTextTexture.getHeight());
	
	
	
	// Distance
	distanceText.str("");
	distanceText << "Distance: " << m_pWorldManager->getPlayer()->getDistance() << "m";
	if (!m_DistanceTextTexture.loadFromRenderedText(distanceText.str().c_str(), m_TextColor, m_Font))
	{
		printf("Unable to render FPS texture!\n");
	}
	m_DistanceTextTexture.render(PADDING, PADDING);

	// Gravity Info
	gravityText.str("");
	if (m_pWorldManager->getGravityDirection() == GRAVITY_DOWN) gravityText << "Gravity: DOWN";
	else gravityText << "Gravity: UP";
	if (!m_GravityTextTexture.loadFromRenderedText(gravityText.str().c_str(), m_TextColor, m_Font))
	{
		printf("Unable to render FPS texture!\n");
	}
	m_GravityTextTexture.render(PADDING, PADDING + m_DistanceTextTexture.getHeight() + PADDING);
}

void HUD::cleanup()
{
	m_FPSTextTexture.free();
	m_GravityTextTexture.free();
	m_DistanceTextTexture.free();
	m_pWorldManager = nullptr;
	TTF_CloseFont(m_Font);
	m_Font = nullptr;
}
