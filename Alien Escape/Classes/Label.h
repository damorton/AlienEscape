#ifndef LABEL_H
#define	LABEL_H

#include <iostream>
#include <string>
#include "Definitions.h"
#include "Sprite.h"

class Label
{
public:
	
	Label();	
	Label(std::string filename);
	Label(std::string text, SDL_Color color, TTF_Font* font);
	virtual ~Label(){ this->cleanUp(); };
	void setPosition(int x, int y);
	int getPositionX(){ return m_PosX; };
	int getPositionY(){ return m_PosY; };
	void cleanUp();	
	void render();	
	Sprite* getSprite(){ return &m_LabelSprite; };
	
private:
	int m_PosX;
	int m_PosY;
	Sprite m_LabelSprite;
	
	// reminder: release resources in cleanup
};

#endif