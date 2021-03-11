

#include "Asteroid.h"
#include "TextureManager.h"
#include "GameObject.h"


int Asteroid::Split()
{

	return 0;
}


int Asteroid::Render(double alpha)
{

	State state = InterpolateState(alpha);
	previousState = currentState;

	state.positionX += state.velocityX;
	state.positionY += state.velocityY;
	mDestRect.x = state.positionX;
	mDestRect.y = state.positionY;

	SDL_RenderCopyExF(mRenderer, mTexture, NULL, &mDestRect, angle, NULL, flip);
	return 0;
}


int Asteroid::Update(time_point t)
{

	Move(t);
	return 0;
}

Asteroid::Asteroid(SDL_Renderer* renderer)
{
	SDL_GetRendererOutputSize(renderer, &w, &h);
	mRenderer = renderer;
	mSrcRect = { 256, 256, 128, 128 };
	mDestRect = { 256, 256, 256, 256 };
	currentState = { 10, 0, 0, 256, 256 };
	previousState = { 10, 0, 0, 256, 256 };
	IMG_Init(IMG_INIT_PNG);
	const char* bigAsteroid = "assets/bigAsteroids.png";

	mTexture = TextureManager::LoadTexture(bigAsteroid, mRenderer);

}

int Asteroid::Move(time_point t)
{
	speed = 5;

	currentState.directionX = speed * sinf(dt / 1s);
	currentState.directionY = speed * cosf(dt / 1s);

	Integrate(currentState, t);

	return 0;
}

int Asteroid::Spawn()
{
//TODO the stuff from the constructor that makes the thing appear on screen should move here. Or this should be a mehtod to place it in the correct vector that gets rendered on screen (in Game.Render())
	return 0;
}



//std::cout << "up" << std::endl;
