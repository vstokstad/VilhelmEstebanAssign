

#include "Asteroid.h"
#include "TextureManager.h"
#include "GameObject.h"


int Asteroid::Split()
{

	return 0;
}


int Asteroid::Render(double alpha)
{


	mDestRect.x = mPosition.x;
	mDestRect.y = mPosition.y;


	angle += angleSpeed;
	SDL_RendererFlip flip = SDL_FLIP_NONE;


	SDL_RenderCopyExF(mRenderer, mTexture, NULL, &mDestRect, angle, NULL, flip);


	return 0;
}


int Asteroid::Update(time_point t)
{

	Move();
	return 0;
}

Asteroid::Asteroid(SDL_Renderer* renderer)
{
	mSrcRect = { 256, 256, 128, 128 };
	mDestRect = { 256, 256, 256, 256 };
	mPosition = Vector2(256, 256);
	mRenderer = renderer;


	IMG_Init(IMG_INIT_PNG);
	const char* bigAsteroid = "assets/bigAsteroids.png";

	mTexture = TextureManager::LoadTexture(bigAsteroid, mRenderer);
	SDL_GetRendererOutputSize(mRenderer, &w, &h);

}

int Asteroid::Move()
{
	speed = 5;


	mDirection.x = speed * sinf(randomDirX);
	mDirection.y = speed * cosf(randomDirY);
	mPosition.x += mDirection.x;
	mPosition.y += mDirection.y;

	ScreenWrap();
	return 0;
}

int Asteroid::Spawn()
{
	srandom(time(nullptr));
	randomDirX = random() % 360;
	randomDirY = random() % 360;
	angleSpeed = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 0.05))) - 0.025;
	Move();
	return 0;
}



//std::cout << "up" << std::endl;
