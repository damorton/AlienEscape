#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

//Screen dimension constants
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define XMLDOC "game.xml"
#define SCREEN_FPS 60
#define SCREEN_TICK_PER_FRAME (1000 / SCREEN_FPS)
#define PADDING 5
#define DEBUG 0

enum Gravity
{
	GRAVITY_UP,
	GRAVITY_DOWN
};

//Game states
enum GameStates
{
	STATE_NULL,
	STATE_INTRO,
	STATE_TITLE,
	STATE_GREEN_OVERWORLD,
	STATE_RED_ROOM,
	STATE_BLUE_ROOM,
	STATE_EXIT,
};

#endif 
