//
// Created by Vilhelm Stokstad on 2021-02-22.
//



#include "Player.h"
#include <iostream>


int Player::HandleInput(SDL_Event event)
{
	if (event.key.keysym.sym == mUp) {
		mDirection.y--;
		std::cout << "up" << std::endl;
	}
	if (event.key.keysym.sym == mDown) {
		mDirection.y++;
		std::cout << "down" << std::endl;
	}
	if (event.key.keysym.sym == mLeft) {
		mDirection.x--;
		std::cout << "left" << std::endl;
	}
	if (event.key.keysym.sym == mRight) {
		mDirection.x++;
		std::cout << "right" << std::endl;
	}
	if (event.key.keysym.sym == mSpace) {
		Fire();
		std::cout << "fire" << std::endl;
	}


	return 0;
}


int Player::Move()
{
	mPosition.x += mDirection.x;
	mPosition.y += mDirection.y;

	mSrcR.x = mDestR.x;
	mSrcR.y = mDestR.y;
	mDestR.x = mPosition.x;
	mDestR.y = mPosition.y;
	return 0;
}

int Player::Fire()
{
	return 0;
}

int Player::Rendering()
{

	SDL_RenderCopy(mPlayerRenderer, mPlayerTex, NULL, &mDestR);

	return 0;
}

int Player::Update()
{

	mDestR.w = 64;
	mDestR.h = 64;
	Move();
	return 0;

}

int Player::Init(SDL_Renderer* playerRenderer)
{

	mPlayerRenderer = playerRenderer;
	mSrcR = SDL_Rect{ .w=64, .h=64 };
	mDestR = SDL_Rect{ .w=64, .h=64 };


	IMG_Init(IMG_INIT_PNG);
	const char* playerWhite = "../assets/playerWhite.png";

	SDL_Surface* tmpSurface = IMG_Load(playerWhite);
	mPlayerTex = SDL_CreateTextureFromSurface(mPlayerRenderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	return 0;

}

Player::Player()
= default;













