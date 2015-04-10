#include <iostream>
#include "Player.h"
#include "GameScene.h"
#include "WorldManager.h"


bool Player::init()
{		
	m_pWorldManager = WorldManager::getInstance();

	//Initialize the offsets
	m_PosX = SCREEN_WIDTH * .10;
	m_PosY = SCREEN_HEIGHT - m_PlayerSprite.getHeight();

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

	m_bIsJumping = false;
	m_fDeltaTime = 0;
	m_nNumberOfJumps = 0;
	return true;
}

void Player::handleEvent(SDL_Event& e)
{	
	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		if (m_pWorldManager->getGravityDirection() == GRAVITY_DOWN && e.key.keysym.sym == SDLK_UP) this->jump();
		else if (m_pWorldManager->getGravityDirection() == GRAVITY_UP && e.key.keysym.sym == SDLK_DOWN) this->jump();
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
	if (!m_bIsJumping)
	{
		m_nNumberOfJumps++;
		m_bIsJumping = true;
		if (m_pWorldManager->getGravityDirection() == GRAVITY_DOWN)
		{
			m_VelY -= MAX_JUMP_VELOCITY;			
		}
		else
		{		
			m_VelY += MAX_JUMP_VELOCITY;		
		}
	}
}

void Player::move(float timeStep)
{
	m_fDeltaTime = timeStep;	
	/*
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
	*/

	//Move the player up or down
	m_PosY += m_VelY * timeStep;

	//If the player went too far up or down
	if (m_PosY < FLOOR_POSITION)
	{
		m_PosY = FLOOR_POSITION;
		m_bIsJumping = false;
		m_VelY = 0;
	}
	else if (m_PosY > SCREEN_HEIGHT - m_PlayerSprite.getHeight() - ROOF_POSITION)
	{
		m_PosY = SCREEN_HEIGHT - m_PlayerSprite.getHeight() - ROOF_POSITION;
		m_bIsJumping = false;
		m_VelY = 0;
	}

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

	if (m_nNumberOfJumps > 3)
	{
		m_pWorldManager->flipGravity();
		m_nNumberOfJumps = 0;
	}

	// Distance
	m_nDistance++;
	m_nDistanceScore = m_nDistance / SCREEN_FPS;
	if (m_nDistanceScore > 0 && m_nDistanceScore % 2 == 0 && m_pWorldManager->getGameWorldSpeed() < MAX_SPEED) m_pWorldManager->increaseGameWorldSpeed();
}

void Player::render()
{	
	//Render current frame
	SDL_Rect* currentClip = &gSpriteClips[m_nFrame / SPRITE_ANIMATION_SPEED];
	m_PlayerSprite.render((int)m_PosX, (int)m_PosY, currentClip,NULL, NULL, m_pWorldManager->getRendererFlip());
	
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
	m_PlayerSprite.free();	
}

