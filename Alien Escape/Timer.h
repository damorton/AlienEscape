#include <SDL.h>

class Timer
{
public:
	Timer();
	void start();
	void stop();
	void pause();
	void unpause();
	Uint32 getTicks();
	bool isStarted();
	bool isPaused();
private:
	Uint32 m_nStartTicks;	
	Uint32 m_nPausedTicks;
	bool m_bPaused;
	bool m_bStarted;
};
