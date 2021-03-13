//
// Created by Vilhelm Stokstad on 2021-03-13.
//

#include "Bullet.h"
#include "Player.h"

int Bullet::CollisionDetection(GameObject* gameObject)
{
	SDL_Rect* sdlRect = &gameObject->mCollider;
	if (SDL_HasIntersection(&mDestRect, sdlRect) == SDL_TRUE) {
		std::cout << "collision" << std::endl;
		OnHit(gameObject);
		return 1;
	}
	return 0;
}

int Bullet::OnHit(GameObject* gameObject)
{
	gameObject->GameObject::~GameObject();
	this->Bullet::~Bullet();
	return 0;
}

int Bullet::Move()
{

	mDestRect.x = (directionX * speed) * dt / 1s;
	mDestRect.y = (directionY * speed) * dt / 1s;

ScreenWrap();
	return 0;
}

int Bullet::Update()
{
	if (isActive) {
		mLifeTime--;
		if (mLifeTime <= 0) {
			this->Bullet::~Bullet();
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
	mDestRect.x = mPlayer->currentState.positionX + mPlayer->currentState.directionX;
	mDestRect.y = mPlayer->currentState.positionY + mPlayer->currentState.directionY;;


	return 0;
}

int Bullet::ScreenWrap()
{

	int o = mDestRect.w;

	if (mDestRect.x > w + o) {
		mDestRect.x = 0 - o;
	}
	else if (mDestRect.x < 0.0 - o) {
		mDestRect.x = w + o;
	}
	if (mDestRect.y > h + o) {
		mDestRect.y = 0 - o;
	}
	else if (mDestRect.y < 0.0 - o) {
		mDestRect.y = h + o;
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
