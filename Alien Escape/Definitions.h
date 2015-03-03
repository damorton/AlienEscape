#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define XMLDOC "game.xml"
#define SCREEN_FPS 60
#define SCREEN_TICK_PER_FRAME (1000 / SCREEN_FPS)
#define PADDING 5
#define DEBUG 1

enum Gravity
{
	GRAVITY_UP,
	GRAVITY_DOWN
};

enum GameStates
{
	STATE_NULL,
	STATE_INTRO,
	STATE_TITLE,	
	STATE_PLAY,
	STATE_PAUSE,
	STATE_END,
};

#endif 
