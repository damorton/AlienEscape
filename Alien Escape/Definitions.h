#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

//Screen dimension constants
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define XMLDOC "game.xml"

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
