#include "HUD.h"
#include "WorldManager.h"
#include "GameScene.h"
#include "Label.h"

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

	m_PauseButton = new Label("Buttons/Pause.png");
	m_PauseButton->setPosition(SCREEN_WIDTH - m_PauseButton->getSprite()->getWidth() - PADDING, PADDING);
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

void HUD::handleEvent(SDL_Event& e)
{
	//If mouse event happened
	if (e.type == SDL_MOUSEMOTION || e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);

		//Check if mouse is in button
		
		
		bool inside = true;

		//Mouse is left of the button
		if (x < m_PauseButton->getPositionX())
		{
			inside = false;
		}
		//Mouse is right of the button
		else if (x > m_PauseButton->getPositionX() + m_PauseButton->getSprite()->getWidth())
		{
			inside = false;
		}
		//Mouse above the button
		else if (y < m_PauseButton->getPositionY())
		{
			inside = false;
		}
		//Mouse below the button
		else if (y > m_PauseButton->getPositionY() + m_PauseButton->getSprite()->getHeight())
		{
			inside = false;
		}

		//Mouse is outside button
		if (!inside)
		{
			
		}
		//Mouse is inside button
		else
		{
			//Set mouse over sprite
			switch (e.type)
			{
			case SDL_MOUSEMOTION:
				//mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
				break;

			case SDL_MOUSEBUTTONDOWN:
				m_pWorldManager->getRunningScene()->pause();
				break;

			case SDL_MOUSEBUTTONUP:
				//mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
				break;
			}
		}
		
	}
}


void HUD::render()
{
	
	m_PauseButton->render();

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

	delete m_PauseButton;
	m_PauseButton = nullptr;

	m_pWorldManager = nullptr;
	TTF_CloseFont(m_Font);
	m_Font = nullptr;
}
