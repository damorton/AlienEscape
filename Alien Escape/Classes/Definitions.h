#ifndef DEFINITIONS_H_
#define DEFINITIONS_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

// Config
#define XMLDOC "Config.xml"
#define DEBUG true
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_FPS 60
#define SCREEN_TICK_PER_FRAME (1000 / SCREEN_FPS)
#define PADDING 5
#define COLOR_WHITE {255, 255, 255, 255}

// Game world
#define GRAVITY 100
#define WORLD_SPEED 4.0f
#define MAX_SPEED 15.0f
#define SPEED_INC 0.02f
#define SPEED_DEC 0.02f
#define FLOOR_POSITION 30
#define ROOF_POSITION 30

// Player
#define WALKING_ANIMATION_FRAMES 4
#define SPRITE_ANIMATION_SPEED 5
#define MAX_JUMP_VELOCITY 1700
#define MAX_ENEMY_SPEED 1500

enum Gravity
{
	GRAVITY_UP,
	GRAVITY_DOWN
};

#endif 
