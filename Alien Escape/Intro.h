#ifndef INTRO_H_
#define INTRO_H_

#include "GameState.h"
#include <SDL.h>

class Intro : public GameState
{
private:
	//Intro background
	SDL_Surface *background;

	//Intro message
	SDL_Surface *message;

public:
	//Loads intro resources
	Intro();
	//Frees intro resources
	~Intro();

	//Main loop functions
	void handle_events();
	void logic();
	void render();
};