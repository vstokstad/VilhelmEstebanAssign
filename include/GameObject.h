#pragma once

#include "include.h"
#include "TextureManager.h"

class GameObject
{

public:
	GameObject() = default;

	explicit GameObject(const char* texturesheet, SDL_Renderer* ren, int ypos = 64, int xpos = 64) : mYpos(ypos),
	                                                                                                 mXpos(xpos)
	{}

	~GameObject() = default;


	int Update()
	{
		mXpos = 0;
		mYpos = 0;

		srcRect.h = 64;
		srcRect.w = 64;
		srcRect.x = 0;
		srcRect.y = 0;

		destRect.x = mXpos;
		destRect.y = mYpos;
		destRect.w = srcRect.w * 2;
		destRect.h = srcRect.h * 2;
		return 0;
	}

	int Render()
	{

		SDL_RenderCopy(this->renderer, this->objTexture, NULL, &destRect);
		return 0;

	};

	int mXpos = {};
	int mYpos = {};


	SDL_Texture* objTexture = nullptr;
	SDL_Rect srcRect = {};
	SDL_Rect destRect = {};
	SDL_Renderer* renderer = nullptr;
};

