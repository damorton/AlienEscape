#include <iostream>
#include "Player.h"
#include "Definitions.h"
#include "GameManager.h"

bool Player::init()
{		
	//Initialize the offsets
	m_PosX = 0;
	m_PosY = 0;

	//Initialize the velocity
	m_VelX = 0;
	m_VelY = 0;

	m_nFrame = 0;
	
	//Set sprite clips
	gSpriteClips[0].x = 0;
	gSpriteClips[0].y = 0;
	gSpriteClips[0].w = 32;
	gSpriteClips[0].h = 103;

	gSpriteClips[1].x = 32;
	gSpriteClips[1].y = 0;
	gSpriteClips[1].w = 32;
	gSpriteClips[1].h = 103;

	gSpriteClips[2].x = 64;
	gSpriteClips[2].y = 0;
	gSpriteClips[2].w = 32;
	gSpriteClips[2].h = 103;

	gSpriteClips[3].x = 96;
	gSpriteClips[3].y = 0;
	gSpriteClips[3].w = 32;
	gSpriteClips[3].h = 103;

	return true;
}

void Player::handleEvent(SDL_Event& e)
{
	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: m_VelY -= maxVelocity; break;
		case SDLK_DOWN: m_VelY += maxVelocity; break;
		case SDLK_LEFT: m_VelX -= maxVelocity; break;
		case SDLK_RIGHT: m_VelX += maxVelocity; break;
		}
	}
	//If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP: m_VelY += maxVelocity; break;
		case SDLK_DOWN: m_VelY -= maxVelocity; break;
		case SDLK_LEFT: m_VelX += maxVelocity; break;
		case SDLK_RIGHT: m_VelX -= maxVelocity; break;
		}
	}
}

void Player::move(float timeStep)
{
	//Move the dot left or right
	m_PosX += m_VelX * timeStep;

	//If the dot went too far to the left or right
	if (m_PosX < 0)
	{
		m_PosX = 0;
	}
	else if (m_PosX > SCREEN_WIDTH - m_PlayerSprite.getWidth() / WALKING_ANIMATION_FRAMES)
	{
		m_PosX = SCREEN_WIDTH - m_PlayerSprite.getWidth() / WALKING_ANIMATION_FRAMES;
	}

	//Move the dot up or down
	m_PosY += m_VelY * timeStep;

	//If the dot went too far up or down
	if (m_PosY < 0)
	{
		m_PosY = 0;
	}
	else if (m_PosY > SCREEN_HEIGHT - m_PlayerSprite.getHeight())
	{
		m_PosY = SCREEN_HEIGHT - m_PlayerSprite.getHeight();
	}
}

void Player::render()
{	
	//Render current frame
	SDL_Rect* currentClip = &gSpriteClips[m_nFrame / 4];
	m_PlayerSprite.render((int)m_PosX, (int)m_PosY, currentClip);
	
	//Go to next frame
	++m_nFrame;

	//Cycle animation
	if (m_nFrame / 4 >= WALKING_ANIMATION_FRAMES)
	{
		m_nFrame = 0;
	}
}

void Player::cleanUp()
{		
	m_PlayerSprite.free();	
}

