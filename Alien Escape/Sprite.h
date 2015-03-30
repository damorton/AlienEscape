#ifndef SPRITE_H
#define SPRITE_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>

class Sprite
{
public:
	Sprite();
	~Sprite();
	bool loadFromFile(std::string path);
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font* font);
	void free();
	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	void setBlendMode(SDL_BlendMode blending);
	void setAlpha(Uint8 alpha);
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);
	int getWidth();
	int getHeight();
private:
	SDL_Texture* mTexture;
	int mWidth;
	int mHeight;
	// reminder: release resources in cleanup
};

#endif 