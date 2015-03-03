#include "Timer.h"

Timer::Timer()
{
	m_nStartTicks = 0;
	m_nPausedTicks = 0;
	m_bPaused = false;
	m_bStarted = false;
}

void Timer::start()
{
	m_bStarted = true;
	m_bPaused = false;
	m_nStartTicks = SDL_GetTicks();
	m_nPausedTicks = 0;
}

void Timer::stop()
{
	m_bStarted = false;
	m_bPaused = false;
	m_nStartTicks = 0;
	m_nPausedTicks = 0;
}

void Timer::pause()
{
	if (m_bStarted && !m_bPaused)
	{
		m_bPaused = true;
		m_nPausedTicks = SDL_GetTicks() - m_nStartTicks;
		m_nStartTicks = 0;
	}
}

void Timer::unpause()
{
	if (m_bStarted && m_bPaused)
	{
		m_bPaused = false;
		m_nStartTicks = SDL_GetTicks() - m_nPausedTicks;
		m_nPausedTicks = 0;
	}
}

Uint32 Timer::getTicks()
{
	Uint32 time = 0;
	if (m_bStarted)
	{
		if (m_bPaused)	
		{
			time = m_nPausedTicks;
		}
		else
		{
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
	return m_bPaused && m_bStarted;
}

