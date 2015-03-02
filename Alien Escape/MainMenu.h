#ifndef MAINMENU_H_
#define MAINMENU_H_

#include "GameState.h"
#include <SDL.h>

class MainMenu : public GameState
{
private:
	//MainMenu screen background
	SDL_Surface *background;

	//MainMenu screen message
	SDL_Surface *message;

public:
	//Loads MainMenu screen resources
	MainMenu();
	//Frees MainMenu resources
	~MainMenu();

	//Main loop functions
	void handle_events();
	void logic();
	void render();
};

#endif 
