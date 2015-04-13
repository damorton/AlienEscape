/*
Sprite.h

Sprite is a game node that contains a pointer to an SDL_Texture.
Contains texture width, height and all texture information. The Sprite 
object handles all rendering of the sprites textures and loading necessary image files from the
games XML config file.

@author	David Morton K00179391
@date	13.4.15
*/
#ifndef SPRITE_H
#define SPRITE_H

//Includes
#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include "Node.h"

//Forward Declarations
class WorldManager;

class Sprite : public Node
{
public:
	Sprite();
	~Sprite();

	/*
		Load sprite image from a file

		@param string path filepath to game resource

		@return bool success of sprite creation
	*/
	bool loadFromFile(std::string path);
	
	/*
		Load sprite using parameter text, used for Sprites with text display

		@param string textureText string to render
		@param SDL_Color textColor used for rendered string
		@param TTF_Font* pointer to the Font used for sprite string

		@return bool success of sprite creation
	*/
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor, TTF_Font* font);

	//Release all Sprite resources
	void free();

	/*
		Set the color of the rendered Sprite texture 

		@param Uint8 red value for red component
		@param Uint8 green value for green component
		@param Uint8 blue value for blue component
	*/
	void setColor(Uint8 red, Uint8 green, Uint8 blue);

	/*
		Set and enable alpha blending mode for game renderer. Blending options:

		SDL_BLENDMODE_NONE = 0x00000000
		SDL_BLENDMODE_BLEND = 0x00000001
		SDL_BLENDMODE_ADD = 0x00000002      
		SDL_BLENDMODE_MOD = 0x00000004

		Allows the texture to be blended with another texture using alpha 
		blending that modifies the alpha value of each texture.		
	*/
	void setBlendMode(SDL_BlendMode blending);

	/*
		Set the alpha value of the texture

		@param Uint8 alpha value of the texture
	*/
	void setAlpha(Uint8 alpha);

	/*
		Render the Sprite texture. Set angle, flip and position

		@param int x position of sprite
		@param int y position of sprite
		@param SDL_Rect* clip clipped image of the sprite sheet
		@param double angle used to render texture
		@param SDL_Point* center of the texture
		@param SDL_RendererFlip flip mode of the renderer
	*/
	void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Getters
	int getWidth();
	int getHeight();
private:
	WorldManager* m_pWorldManager;
	SDL_Texture* mTexture;
	int mWidth;
	int mHeight;
	// reminder: release resources in cleanup
};

#endif 