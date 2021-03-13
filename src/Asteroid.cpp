

#include "Asteroid.h"
#include "TextureManager.h"
#include "GameObject.h"

int Asteroid::Split()
{

	return 0;
}


int Asteroid::Update(time_point t)
{
	std::cout << RandomWithUpper() << std::endl;
	Move(t);
	return 0;
}

Asteroid::Asteroid(SDL_Renderer* renderer)
{
	SDL_GetRendererOutputSize(renderer, &w, &h);
	mRenderer = renderer;
	mDestRect = { 256, 256, 256, 256 };
	mCollider = { 256 - (256 / 6), 256 - (256 / 6), 128, 128 };
	currentState = { RandomWithUpper(), 0, 0, 0, RandomWithUpper()*100, RandomWithUpper()*100 ,RandomWithUpper(), RandomWithUpper() };
	previousState = { 0, 0, 0, 0, 256, 256 };
	IMG_Init(IMG_INIT_PNG);
	const char* bigAsteroid = "assets/bigAsteroids.png";

	mTexture = TextureManager::LoadTexture(bigAsteroid, mRenderer);

}

double Asteroid::RandomWithUpper()
{
	return static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

int Asteroid::Move(time_point t)
{
	speed = RandomWithUpper()*10;
	currentState.accelerationX = RandomWithUpper();
	currentState.accelerationY = RandomWithUpper();

	previousState = currentState;
	Integrate(currentState, t);
	return 0;
}

int Asteroid::Spawn()
{
//TODO the stuff from the constructor that makes the thing appear on screen should move here. Or this should be a mehtod to place it in the correct vector that gets rendered on screen (in Game.Render())
	return 0;
}



