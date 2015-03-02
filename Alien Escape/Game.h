#ifndef GAME_H_
#define GAME_H_

#include "GameState.h"
#include <SDL.h>

class Game : public GameState
{
private:
	//Level dimensions
	const static int LEVEL_WIDTH = 1280;
	const static int LEVEL_HEIGHT = 960;

	//Game background
	SDL_Surface *background;
	
public:
	//Loads resources and initializes objects
	Game(int prevState);

	//Frees resources
	~Game();

	//Main loop functions
	void handle_events();
	void logic();
	void render();
};

#endif
