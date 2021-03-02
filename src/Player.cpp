//
// Created by Vilhelm Stokstad on 2021-02-22.
//



#include "Player.h"
#include <iostream>


int Player::HandleInput(SDL_Event event)
{
	if (event.key.keysym.sym == mUp) {
		mDirection.y = Library::Lerp(mDirection.y, 1.0f, 1.0f);
		std::cout << "up" << std::endl;
	}
	if (event.key.keysym.sym == mDown) {
		mDirection.y = Library::Lerp(mDirection.y, -1.0f, 1.0f);
		std::cout << "down" << std::endl;
	}
	if (event.key.keysym.sym == mLeft) {
		mDirection.x = Library::Lerp(mDirection.x, -1.0f, 1.0f);
		std::cout << "left" << std::endl;
	}
	if (event.key.keysym.sym == mRight) {
		mDirection.x = Library::Lerp(mDirection.x, 1.0f, 1.0f);
		std::cout << "right" << std::endl;
	}
	if (event.key.keysym.sym == mSpace) {
		Fire();
		std::cout << "fire" << std::endl;
	}

	Move();
	return 0;
}


int Player::Move()
{


	mPosition.x = Library::Lerp(mPosition.x, mDirection.x, 0.2F);
	mPosition.y = Library::Lerp(mPosition.y, mDirection.y, 0.2F);
	mDestR->x = mPosition.x;
	mDestR->y = mPosition.y;
	return 0;
}

int Player::Fire()
{
	return 0;
}

int Player::Rendering()
{

	SDL_RenderCopy(mPlayerRenderer, mPlayerTex, mSrcR, mDestR);

	return 0;
}

int Player::Update()
{

	cnt++;
	mDestR->x = cnt;
	return 0;

}

int Player::Init(SDL_Renderer* playerRenderer)
{

	mPlayerRenderer = playerRenderer;
	mSrcR = new SDL_Rect{ .w=32, .h=32, };
	mDestR = new SDL_Rect{ .w=32, .h=32 };





	IMG_Init(IMG_INIT_PNG);
	const char* playerWhite = "../assets/playerWhite.png";

	SDL_Surface* tmpSurface = IMG_Load(playerWhite);
	mPlayerTex = SDL_CreateTextureFromSurface(mPlayerRenderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	return 0;

}

Player::Player()
= default;













