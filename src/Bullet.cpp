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
	speed = 50;
	mDestRect.x += (directionX * speed) * dt / 1s;
	mDestRect.y += (directionY * speed) * dt / 1s;

	ScreenWrap();
	return 0;
}

int Bullet::Update()
{
	if (isActive) {
		std::cout << --mLifeTime << std::endl;
		if (mLifeTime <= 0) {
			isActive = false;
			mLifeTime = 5000;
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
	mDestRect.x = mPlayer->currentState.positionX + directionX;
	mDestRect.y = mPlayer->currentState.positionY + directionY;
	speed = speed + (mPlayer->currentState.velocityX + mPlayer->currentState.velocityY);
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
	isActive = false;
	SDL_GetRendererOutputSize(renderer, &w, &h);
	mRenderer = renderer;
	mTexture = texture;
}

int Bullet::Render(double alpha)
{
	SDL_RenderCopy(mRenderer, mTexture, NULL, &mDestRect);
	return 0;
}
