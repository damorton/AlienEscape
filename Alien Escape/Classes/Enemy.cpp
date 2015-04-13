/*
Enemy.cpp

In game enemy containing Sprite information

@author	David Morton K00179391
@date	13.4.15
*/
#include <iostream>
#include "Enemy.h"
#include "GameScene.h"
#include "WorldManager.h"
#include "Timer.h"

bool Enemy::init()
{
	m_pWorldManager = WorldManager::getInstance();

	//Initialize the offsets
	m_PosX = SCREEN_WIDTH;
	m_PosY = SCREEN_HEIGHT - m_pSprite.getHeight();

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

	m_eState = ALIVE;
	m_bIsJumping = false;
	m_fDeltaTime = 0;	

	return true;
}

void Enemy::handleEvent(SDL_Event& e)
{	
	//If a key was pressed mimic player jumping
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Jump direction change based on gravity
		if (m_pWorldManager->getGravityDirection() == GRAVITY_DOWN && e.key.keysym.sym == SDLK_UP) this->jump();
		else if (m_pWorldManager->getGravityDirection() == GRAVITY_UP && e.key.keysym.sym == SDLK_DOWN) this->jump();
	}		
}

void Enemy::jump()
{	
	if (!m_bIsJumping)
	{		
		m_bIsJumping = true;
		if (m_pWorldManager->getGravityDirection() == GRAVITY_DOWN)
		{
			m_VelY -= MAX_JUMP_VELOCITY * .5;
		}
		else
		{
			m_VelY += MAX_JUMP_VELOCITY * .5;
		}
	}
	
}

void Enemy::move(float timeStep)
{	
	//Move the Sprite smoothly
	m_fDeltaTime = timeStep;		
	m_VelX = -m_pWorldManager->getGameWorldSpeed() * 60;

	//Move the dot left or right
	m_PosX += m_VelX * m_fDeltaTime;
	//Update bounding Box
	m_pSprite.getBoundBox()->x = m_PosX;
	
	//If the dot went too far to the left or right
	if (m_PosX < -m_pSprite.getWidth())
	{
		m_PosX = SCREEN_WIDTH;
		m_eState = ALIVE;
	}	
	
	//Move the Enemy up or down and update the bounding box
	m_PosY += m_VelY * m_fDeltaTime;
	m_pSprite.getBoundBox()->y = m_PosY;

	//If the Enemy went too far up or down
	if (m_PosY < FLOOR_POSITION)
	{
		m_PosY = FLOOR_POSITION;	
		m_bIsJumping = false;
		m_VelY = 0;
	}
	else if (m_PosY > SCREEN_HEIGHT - m_pSprite.getHeight() - ROOF_POSITION)
	{
		m_PosY = SCREEN_HEIGHT - m_pSprite.getHeight() - ROOF_POSITION;		
		m_bIsJumping = false;
		m_VelY = 0;
	}

	/*
	// Gravity
	if (m_bIsJumping)
	{
		if (m_pWorldManager->getGravityDirection() == GRAVITY_DOWN)
		{
			m_VelY += GRAVITY;
		}
		else
		{
			m_VelY -= GRAVITY;
		}
	}
	*/

	// Gravitational force direction
	if (m_pWorldManager->getGravityDirection() == GRAVITY_DOWN)
	{
		m_VelY += GRAVITY;
	}
	else
	{
		m_VelY -= GRAVITY;
	}
}

void Enemy::render()
{
	//Render current frame
	SDL_Rect* currentClip = &gSpriteClips[m_nFrame / SPRITE_ANIMATION_SPEED];
	m_pSprite.render((int)m_PosX, (int)m_PosY, currentClip, NULL, NULL, m_pWorldManager->getRendererFlip());

	//Go to next frame
	++m_nFrame;

	//Cycle animation
	if (m_nFrame / SPRITE_ANIMATION_SPEED >= WALKING_ANIMATION_FRAMES)
	{
		m_nFrame = 0;
	}
}

void Enemy::cleanUp()
{
	m_pSprite.free();
}

