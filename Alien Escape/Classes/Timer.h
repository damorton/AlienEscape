/*
Timer.h

Timer object used to keep track of game ticks. Used for FPS limiting, delta timer, and 
other in game timers.

@author	David Morton K00179391
@date	13.4.15
*/
//Includes
#include <SDL.h>

class Timer
{
public:
	Timer();	

	//Timer controls
	void start();
	void stop();
	void pause();
	void unpause();

	//Get CPU ticks since the program started
	Uint32 getTicks();

	//Get timer status
	bool isStarted();
	bool isPaused();
private:
	Uint32 m_nStartTicks;	
	Uint32 m_nPausedTicks;
	bool m_bPaused;
	bool m_bStarted;
};
