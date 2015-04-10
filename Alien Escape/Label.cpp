#include <iostream>
#include "Label.h"

Label::Label(std::string filename)
{
	m_PosX = 0;
	m_PosY = 0;
	m_LabelSprite.loadFromFile(filename);
}

Label::Label(std::string text, SDL_Color color, TTF_Font* font)
{
	m_PosX = 0;
	m_PosY = 0;
	m_LabelSprite.loadFromRenderedText(text.c_str(), color, font);
}

void Label::setPosition(int x, int y)
{
	m_PosX = x;
	m_PosY = y;
}

void Label::render()
{	
	m_LabelSprite.render(m_PosX, m_PosY);
}

void Label::cleanUp()
{
	m_LabelSprite.free();
}

