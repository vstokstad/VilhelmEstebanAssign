//
// Created by Vilhelm Stokstad on 2021-03-13.
//

#include "Bullet.h"
#include "Player.h"
#include "Asteroid.h"

int Bullet::CollisionDetection(Asteroid* asteroid)
{
	SDL_Rect* sdlRect = &asteroid->mCollider;
	if (SDL_HasIntersection(&mDestRect, sdlRect) == SDL_TRUE) {

		OnHit(asteroid);
		return 1;
	}
	return 0;
}

int Bullet::OnHit(Asteroid* asteroid)
{

	asteroid->isActive = false;
	asteroid->Split();
	std::cout << "HIT!" << std::endl;
	mLifeTime = 500;
	this->isActive = false;
	return 0;
}

int Bullet::Move()
{
	speed = 1;

	mDestRect.x += directionX * dt / 1s;
	mDestRect.y += directionY * dt / 1s;

	ScreenWrap();
	return 0;
}

int Bullet::Update()
{
	if (isActive) {
	--mLifeTime;
		if (mLifeTime <= 0) {
			isActive = false;
			mLifeTime = 500;
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

	mDestRect.x = mPlayer->currentState.positionX;
	mDestRect.y = mPlayer->currentState.positionY;


	return 0;
}

int Bullet::ScreenWrap()
{

	int o = mDestRect.w;

	if (mDestRect.x > w + o) {
		this->isActive = false;
	}
	else if (mDestRect.x < 0.0 - o) {
		this->isActive = false;
	}
	if (mDestRect.y > h + o) {
		this->isActive = false;
	}
	else if (mDestRect.y < 0.0 - o) {
		this->isActive = false;
	}
	return 0;
}

Bullet::Bullet(SDL_Renderer* renderer, Player* player, SDL_Texture* texture) : mPlayer(player), mTexture(texture), mRenderer(renderer)
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
	if (isActive){
	SDL_RenderCopy(mRenderer, mTexture, NULL, &mDestRect);

	}
	return 0;
}
