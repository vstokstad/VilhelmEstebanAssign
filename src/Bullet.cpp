//
// Created by Vilhelm Stokstad on 2021-03-13.
//

#include "Bullet.h"
#include "Player.h"
#include "Asteroid.h"

int Bullet::CollisionDetection(Asteroid* gameObject)
{
	SDL_Rect* sdlRect = &gameObject->mCollider;
	if (SDL_HasIntersection(&mDestRect, sdlRect) == SDL_TRUE) {

		OnHit(gameObject);
		return 1;
	}
	return 0;
}

int Bullet::OnHit(Asteroid* asteroid)
{
	std::cout << "HIT!" << std::endl;
	asteroid->Split();
	mLifeTime = 5000;
	this->isActive = false;
	return 0;
}

int Bullet::Move()
{
	speed = 100;
	mDestRect.x += (directionX * speed) * dt / 1s;
	mDestRect.y += (directionY * speed) * dt / 1s;

	ScreenWrap();
	return 0;
}

int Bullet::Update()
{
	if (isActive) {
	--mLifeTime;
		if (mLifeTime <= 0) {
			isActive = false;
			mLifeTime = 1000;
			return 0;
		}
		Move();
	}
	return 0;
}

int Bullet::OnGetFired()
{
	isActive = true;
	directionX = mPlayer->currentState.directionX;
	directionY = mPlayer->currentState.directionY;
	mDestRect.x = mPlayer->currentState.positionX ;
	mDestRect.y = mPlayer->currentState.positionY ;

	Update();

	return 0;
}

int Bullet::ScreenWrap()
{

	int o = mDestRect.w;

	if (mDestRect.x > w + o) {
		Bullet::~Bullet();
	}
	else if (mDestRect.x < 0.0 - o) {
		Bullet::~Bullet();
	}
	if (mDestRect.y > h + o) {
		Bullet::~Bullet();
	}
	else if (mDestRect.y < 0.0 - o) {
		Bullet::~Bullet();
	}
	return 0;
}

Bullet::Bullet(SDL_Renderer* renderer, Player* player, SDL_Texture* texture) : mPlayer(player)
{
	IMG_Init(IMG_INIT_PNG);
	isActive = false;
	SDL_GetRendererOutputSize(renderer, &w, &h);
	mRenderer = renderer;
	mTexture = texture;
	mPlayer = player;
}

int Bullet::Render(double alpha)
{
	speed = 1;
	mDestRect.x += (directionX * speed) * dt / 1s;
	mDestRect.y += (directionY * speed) * dt / 1s;
	SDL_RenderCopy(mRenderer, mPlayer->bulletTexture, NULL, &mDestRect);
	return 0;
}
