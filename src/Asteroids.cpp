

#include "Asteroids.h"
#include <iostream>
#include "TextureManager.h"


int Asteroid::Split()
{

	return 0;
}


int Asteroid::Rendering()
{

	SDL_RenderCopy(mAsteroidRenderer, mAsteroidTex, NULL, &mDestR);

	return 0;
}

int Asteroid::Update()
{

	mDestR.w = 64;
	mDestR.h = 64;
	return 0;

}

int Asteroid::Init(SDL_Renderer* mAsteroidRenderer)
{
	mAsteroidRenderer = mAsteroidRenderer;
	mSrcR = SDL_Rect{ mSrcR.w = 64, mSrcR.h = 64 };
	mDestR = SDL_Rect{ mDestR.w = 64, mDestR.h = 64 };

	IMG_Init(IMG_INIT_PNG);
	const char* bigAsteroid = "assets/bigAsteroid.png";

	mAsteroidTex = TextureManager::LoadTexture(bigAsteroid, mAsteroidRenderer);

	return 0;
}

Asteroid::Asteroid()
= default;


