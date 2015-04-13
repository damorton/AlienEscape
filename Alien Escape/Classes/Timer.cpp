/*
Timer.cpp

Timer object used to keep track of game ticks. Used for FPS limiting, delta timer, and
other in game timers.

@author	David Morton K00179391
@date	13.4.15
*/
//Includes
#include "Timer.h"

Timer::Timer()
{
	//Initialize timer
	m_nStartTicks = 0;
	m_nPausedTicks = 0;
	m_bPaused = false;
	m_bStarted = false;
}

void Timer::start()
{
	//Get CPU ticks and start the timer
	m_bStarted = true;
	m_bPaused = false;
	m_nStartTicks = SDL_GetTicks();
	m_nPausedTicks = 0;
}

void Timer::stop()
{
	//Stop the timer and re-initialize the timer values
	m_bStarted = false;
	m_bPaused = false;
	m_nStartTicks = 0;
	m_nPausedTicks = 0;
}

void Timer::pause()
{
	//Pause the timer by storing the current ticks - the ticks value stored on timer start
	if (m_bStarted && !m_bPaused)
	{
		m_bPaused = true;
		m_nPausedTicks = SDL_GetTicks() - m_nStartTicks;
		m_nStartTicks = 0;
	}
}

void Timer::unpause()
{
	//Unpause the timer and store the new start tick value as the current ticks - paused ticks value
	if (m_bStarted && m_bPaused)
	{
		m_bPaused = false;
		m_nStartTicks = SDL_GetTicks() - m_nPausedTicks;
		m_nPausedTicks = 0;
	}
}

Uint32 Timer::getTicks()
{
	//If the timer is paused return the paused ticks value
	Uint32 time = 0;
	if (m_bStarted)
	{
		if (m_bPaused)	
		{
			time = m_nPausedTicks;
		}
		else
		{
			//Return the ticks since program start
			time = SDL_GetTicks() - m_nStartTicks;
		}
	}
	return time;
}

bool Timer::isStarted()
{
	return m_bStarted;
}

bool Timer::isPaused()
{
	//Is paused if started and paused
	return m_bPaused && m_bStarted;
}

