#pragma once
#include "include.h"

class TextureManager 
{
public:
	static SDL_Texture* LoadTexture(const char* texture, SDL_Renderer* ren)
	{
		SDL_Surface* tempSurface = IMG_Load(texture);
		SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tempSurface);
		SDL_FreeSurface(tempSurface);

		return tex;
	}
};


