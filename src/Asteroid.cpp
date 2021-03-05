

#include "Asteroid.h"
#include "TextureManager.h"
#include "RigidBody.h"

int Asteroid::Split()
{

	return 0;
}


int Asteroid::Render(double t, double fdt)
{

	mDestRect->w = 64;
	mDestRect->h = 64;
	SDL_RenderCopy(mRenderer, mTexture, NULL, mDestRect);
	return 0;
}


int Asteroid::Update(double t, double dt)
{
	mDestRect->w = 64;
	mDestRect->h = 64;

	return 0;
}

Asteroid::Asteroid(SDL_Renderer* renderer):mRenderer(renderer)
{
	mSrcRect = new SDL_Rect{64,64};
	mDestRect = new SDL_Rect{ 64, 64 };
	mPosition = Vector2(0, 0);
	mRenderer = renderer;
	Vector2 tempSize = { (float)mDestRect->w, (float)mDestRect->h};
	mRigidBody =  RigidBody(1.f, tempSize, &this->mPosition, this);

	IMG_Init(IMG_INIT_PNG);
	const char* bigAsteroid = "assets/bigAsteroid.png";

	mTexture = TextureManager::LoadTexture(bigAsteroid, mRenderer);

}

int Asteroid::Move(double t, double fdt)
{
	return 0;
}



