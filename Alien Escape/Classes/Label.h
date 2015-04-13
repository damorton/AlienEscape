/*
Label.h

Label is used to display text information or button images.
Contains Sprite information.

@author	David Morton K00179391
@date	13.4.15
*/
#ifndef LABEL_H
#define	LABEL_H

//Includes
#include <iostream>
#include <string>
#include "Definitions.h"
#include "Sprite.h"

class Label
{
public:
	//Constructors
	Label();	
	Label(std::string filename);
	Label(std::string text, SDL_Color color, TTF_Font* font);
	
	virtual ~Label(){ this->cleanUp(); };

	void cleanUp();
	void render();

	//Getters 	
	int getPositionX(){ return m_PosX; };
	int getPositionY(){ return m_PosY; };

	/*
		Get the Labels Sprite information

		@return Sprite information for the label
	*/
	Sprite* getSprite(){ return &m_LabelSprite; };

	//Setters
	void setPosition(int x, int y);	
private:
	int m_PosX;
	int m_PosY;
	Sprite m_LabelSprite; 
	// reminder: release resources in cleanup
};

#endif