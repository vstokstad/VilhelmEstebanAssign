

#include "Asteroid.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "RigidBody.h"


int Asteroid::Split()
{

	return 0;
}


int Asteroid::Render(double t, double fdt)
{

	mDestRect->w = 124;
	mDestRect->h = 124;


	mDestRect->x = (int)mPosition.x;
	mDestRect->y = (int)mPosition.y;


	angle += angleSpeed;
	SDL_RendererFlip flip = SDL_FLIP_NONE;


	SDL_RenderCopyEx(mRenderer, mTexture, NULL, mDestRect, angle, NULL, flip);
	return 0;
}


int Asteroid::Update(double t, double dt)
{
	mDestRect->w = 124;
	mDestRect->h = 124;
	Move();
	return 0;
}

Asteroid::Asteroid(SDL_Renderer* renderer):mRenderer(renderer)
{
	mSrcRect = new SDL_Rect{64,64};
	mDestRect = new SDL_Rect{ 124, 124 };
	mPosition = Vector2(258, 258);
	mRenderer = renderer;
	mRigidBody = RigidBody(0, Vector2(), &this->mPosition, this);
	Vector2 tempSize = { (float)mDestRect->w, (float)mDestRect->h};
	mRigidBody =  RigidBody(1.f, tempSize, &this->mPosition, this);

	IMG_Init(IMG_INIT_PNG);
	const char* bigAsteroid = "assets/bigAsteroids.png";

	mTexture = TextureManager::LoadTexture(bigAsteroid, mRenderer);

}

int Asteroid::Move()
{
	float speed = 1;

	
	

	mDirection.x = speed *sin(randomDirX);
	mDirection.y = speed *cos(randomDirY);
	mPosition = mPosition + mDirection;

	return 0;
}

int Asteroid::Spawn()
{
	srand(time(NULL));
	randomDirX = rand() % 360;
	randomDirY = rand() % 360;

	angleSpeed = (static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / 0.05))) - 0.025;
	std::cout << angleSpeed << std::endl;
	Move();
	return 0;
}



//std::cout << "up" << std::endl;
