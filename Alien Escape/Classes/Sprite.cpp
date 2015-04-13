/*
Sprite.cpp

Sprite is a game node that contains a pointer to an SDL_Texture.
Contains texture width, height and all texture information. The Sprite
object handles all rendering of the sprites textures and loading necessary image files from the
games XML config file.

@author	David Morton K00179391
@date	13.4.15
*/
//Includes
#include <stdio.h>
#include <SDL_image.h>
#include "Sprite.h"
#include "WorldManager.h"

Sprite::Sprite()
{	
	//Initialize the Sprite
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;	
	m_pWorldManager = WorldManager::getInstance();
}

Sprite::~Sprite()
{
	//Clean up all Sprite resources
	printf("Sprite destroyed\n");
	this->free();
}

bool Sprite::loadFromFile(std::string path)
{
	//Free any resources before creating a new texture
	this->free();
	SDL_Texture* newTexture = NULL;

	//Create a surface from the resource at path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Set the transparent color value of the surface
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create a texture from the final surface loadedSurface
		newTexture = SDL_CreateTextureFromSurface(m_pWorldManager->getRenderer(), loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get the surface width and height
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;			
		}
		//Release the loadedSurface resource after creating texture from it
		SDL_FreeSurface(loadedSurface);
	}

	//Store texture as a member of the Sprite
	mTexture = newTexture;
	return mTexture != NULL;
}

bool Sprite::loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font* font)
{	
	//Free any resources before creating a new texture
	free();

	//Create a surface to render the textureText string to. Set the font and the font color.
	SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText.c_str(), textColor);
	if (textSurface != NULL)
	{
		//Create a texture from the textSurface for the renderer
		mTexture = SDL_CreateTextureFromSurface(m_pWorldManager->getRenderer(), textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			mWidth = textSurface->w;
			mHeight = textSurface->h;			
		}

		//Free the surface resources
		SDL_FreeSurface(textSurface);
	}
	else
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}
	return mTexture != NULL;
}

void Sprite::free()
{
	//Release any resources used by the Sprite
	if (mTexture != NULL)
	{
		//Destroy the texture
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void Sprite::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Set the color of the texture. This will affect the color displyed
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void Sprite::setBlendMode(SDL_BlendMode blending)
{
	//Set the blending mode for the texture, used for alpha blending
	SDL_SetTextureBlendMode(mTexture, blending);
}

void Sprite::setAlpha(Uint8 alpha)
{
	//Set alphha value of the texture
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void Sprite::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
	//Create a rectangle to store the dimension of one sprite frame in the sprite sheet
	SDL_Rect renderQuad = { x, y, mWidth, mHeight };
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;

		//Update the Bounding Box dimensions
		m_BoundingBox->w = renderQuad.w;
		m_BoundingBox->h = renderQuad.h;
	}

	//Render the sprite texture using the renderer. Pass in configuration details to the renderer
	//in order set how the texture is rendered. 
	SDL_RenderCopyEx(m_pWorldManager->getRenderer(), mTexture, clip, &renderQuad, angle, center, flip);
}

int Sprite::getWidth()
{
	return mWidth;
}

int Sprite::getHeight()
{
	return mHeight;
}
