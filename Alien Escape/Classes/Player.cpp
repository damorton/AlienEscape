/*
Player.cpp

Player object contains Sprite information. Handles game input and
records players scores

@author	David Morton K00179391
@date	13.4.15
*/
//Includes
#include <iostream>
#include "Player.h"
#include "GameScene.h"
#include "WorldManager.h"
#include "Timer.h"

bool Player::init()
{		
	//Initialize player
	m_pWorldManager = WorldManager::getInstance();	
	//Initialize the offsets
	m_PosX = SCREEN_WIDTH * .05;
	m_PosY = SCREEN_HEIGHT - m_pSprite.getHeight();
	m_TBoostTimer = new Timer();
	//Initialize the velocity
	m_VelX = 0;
	m_VelY = 0;

	//Animation frames
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

	//Player init status
	m_eState = ALIVE;
	m_bIsJumping = false;
	m_fDeltaTime = 0;
	m_nNumberOfJumps = 0;
	m_bBoostEnabled = true;
	m_bIsBoosting = false;

	//Start the Boost timer and pause it
	m_TBoostTimer->start();
	m_TBoostTimer->pause();
	return true;
}

void Player::handleEvent(SDL_Event& e)
{	
	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{		
		//Change jump button based on gravity direction
		if (m_pWorldManager->getGravityDirection() == GRAVITY_DOWN && e.key.keysym.sym == SDLK_UP) this->jump();
		else if (m_pWorldManager->getGravityDirection() == GRAVITY_UP && e.key.keysym.sym == SDLK_DOWN) this->jump();			
	}
		
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//If the space key is pressed
		if (e.key.keysym.sym == SDLK_SPACE)
		{	
			//Boost the player by increasing game speed, unpause the Boost timer clock
			if (m_TBoostTimer->getTicks() < 2000 && m_bBoostEnabled)
			{			
				m_bIsBoosting = true;
				m_fGameSpeed = m_pWorldManager->getGameWorldSpeed();
				m_pWorldManager->setGameWorldSpeed(20);
				m_TBoostTimer->unpause();
			}			
		}			
	}
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//If the space key is released, turn off the player boost and pause the timer
		if (e.key.keysym.sym == SDLK_SPACE)
		{				
			if (m_bIsBoosting)
			{				
				m_bIsBoosting = false;
				m_pWorldManager->setGameWorldSpeed(m_fGameSpeed);
				m_TBoostTimer->pause();				
			}
		}		
	}


	/*
	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		//case SDLK_UP: m_VelY -= maxVelocity; break;
		case SDLK_UP: this->jump(); break;
		//case SDLK_DOWN: m_VelY += maxVelocity; break;
		//case SDLK_LEFT: m_VelX -= maxVelocity; break;
		//case SDLK_RIGHT: m_VelX += maxVelocity; break;
		}
	}
	//If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		//case SDLK_UP: m_VelY += maxVelocity; break;
		//case SDLK_DOWN: m_VelY -= maxVelocity; break;
		//case SDLK_LEFT: m_VelX += maxVelocity; break;
		//case SDLK_RIGHT: m_VelX -= maxVelocity; break;
		}
	}
	*/
}

void Player::jump()
{	
	//Apply velocity to the player based on the direction of gravity
	if (!m_bIsJumping)
	{
		m_nNumberOfJumps++;
		m_bIsJumping = true;
		if (m_pWorldManager->getGravityDirection() == GRAVITY_DOWN)
		{
			//Down force
			m_VelY -= MAX_JUMP_VELOCITY;			
		}
		else
		{		
			//Up force
			m_VelY += MAX_JUMP_VELOCITY;		
		}
	}
	//printf("Player:: Jump velocity %d\n", m_VelY);
}

void Player::move(float timeStep)
{
	//If the boost timer is above 2 seconds disable boost
	if (m_TBoostTimer->getTicks() > 2000)
	{
		m_bBoostEnabled = false;
		m_pWorldManager->setGameWorldSpeed(m_fGameSpeed);		
		m_TBoostTimer->unpause();
	}	
	
	//When the booster is disabled, re-enable the booster after 4 seconds
	//printf("Boost timer : %d\n", m_TBoostTimer->getTicks());
	if (m_TBoostTimer->getTicks() > 6000)
	{
		m_bBoostEnabled = true;
		m_TBoostTimer->start();
		m_TBoostTimer->pause();
	}

	//Store delta time
	m_fDeltaTime = timeStep;	
	
	//Move the player up or down
	m_PosY += m_VelY * m_fDeltaTime;

	// Update bounding Box
	m_pSprite.getBoundBox()->x = m_PosX;
	m_pSprite.getBoundBox()->y = m_PosY;

	//If the player went too far up or down, reset position. Keep them in the cave 
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

	// Gravity
	/*
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
	//Apply gravity based on the force direction
	if (m_pWorldManager->getGravityDirection() == GRAVITY_DOWN)
	{
		m_VelY += GRAVITY;
	}
	else
	{
		m_VelY -= GRAVITY;
	}

	/*
	if (m_nNumberOfJumps > 3)
	{
		m_pWorldManager->flipGravity();
		m_nNumberOfJumps = 0;
	}
	*/

	//Distance score increased based on booster status
	m_nDistance += (m_bIsBoosting) ? 5 : 1;
	m_nDistanceScore = m_nDistance / SCREEN_FPS;

	//Increase the game world speed based on the distance score
	if (m_nDistanceScore > 0 && m_nDistanceScore % 2 == 0 && m_pWorldManager->getGameWorldSpeed() < MAX_SPEED)
	{
		//If the distance score mod 2 == 0 increase speed by a set amount
		m_pWorldManager->increaseGameWorldSpeed();
	}
}

void Player::render()
{		
	//Render current frame of Player sprite
	SDL_Rect* currentClip = &gSpriteClips[m_nFrame / SPRITE_ANIMATION_SPEED];
	m_pSprite.render((int)m_PosX, (int)m_PosY, currentClip,NULL, NULL, m_pWorldManager->getRendererFlip());
	
	//Go to next frame
	++m_nFrame;

	//Cycle animation
	if (m_nFrame / SPRITE_ANIMATION_SPEED >= WALKING_ANIMATION_FRAMES)
	{
		m_nFrame = 0;
	}
}

void Player::cleanUp()
{		
	//Release all resources
	m_pSprite.free();	
}

