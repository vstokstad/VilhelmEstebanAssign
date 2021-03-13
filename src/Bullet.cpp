//
// Created by Vilhelm Stokstad on 2021-03-13.
//

#include "Bullet.h"
#include "TextureManager.h"
#include "Player.h"

int Bullet::CollisionDetection(GameObject* gameObject)
{
	SDL_Rect* sdlRect = &gameObject->mCollider;
	if (SDL_HasIntersection(&mCollider, sdlRect) == SDL_TRUE) {
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

int Bullet::Move(time_point t)
{
	speed = 5;

	previousState = currentState;
	Integrate(currentState, t);


	return 0;
}

int Bullet::Update(time_point t)
{
	if (isActive) {
		mLifeTime--;
		if (mLifeTime <= 0) {
			this->Bullet::~Bullet();
			return 0;
		}

		Move(t);
	}
	return 0;
}

int Bullet::OnGetFired()
{
	isActive = true;
	currentState = { 10, 10, mPlayer->currentState.velocityX * 2, mPlayer->currentState.velocityY * 2,
	                 mPlayer->currentState.positionX, mPlayer->currentState.positionY };
	previousState = { 10, 10, mPlayer->previousState.velocityX, mPlayer->previousState.velocityY,
	                  mPlayer->previousState.positionX, mPlayer->previousState.positionY };
	mDestRect.x = currentState.positionX;
	mDestRect.y = currentState.positionY;

	mCollider.x = mDestRect.x;
	mCollider.y = mDestRect.y;

	return 0;
}

Bullet::Bullet(SDL_Renderer* renderer, Player* player) : mPlayer(player)
{
	flip = SDL_FLIP_HORIZONTAL;
	isActive = false;
	SDL_GetRendererOutputSize(renderer, &w, &h);
	mRenderer = renderer;
	mDestRect = { 16, 16, 16, 16 };
	mCollider = { 16, 64, 16, 16 };
	currentState = { 0, 0, 0, 0, mPlayer->currentState.positionX, mPlayer->currentState.positionY };
	previousState = { 0, 0, 0, 0, mPlayer->currentState.positionX, mPlayer->currentState.positionY };

	const char* bullet = "assets/player.png";

	mTexture = TextureManager::LoadTexture(bullet, mRenderer);
}
