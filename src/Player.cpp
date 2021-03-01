//
// Created by Vilhelm Stokstad on 2021-02-22.
//



#include "Player.h"




void Player::HandleInput(SDL_Event event)
{
	if (event.key.keysym.sym == mUp) {
		mDirection.y = Library::Lerp(mDirection.y, 1.0f, 1.0f);

	}
	if (event.key.keysym.sym == mDown) {
		mDirection.y = Library::Lerp(mDirection.y, -1.0f, 1.0f);

	}
	if (event.key.keysym.sym == mLeft) {
		mDirection.x = Library::Lerp(mDirection.x, -1.0f, 1.0f);

	}
	if (event.key.keysym.sym == mRight) {
		mDirection.x = Library::Lerp(mDirection.x, 1.0f, 1.0f);

	}
	if (event.key.keysym.sym == mSpace) {
		Fire();
	}

	Move();
}


void Player::Move()
{


	mSrcR->x = mPosition.x;
	mSrcR->y = mPosition.y;
	this->mPosition.x = Library::Lerp(this->mPosition.x, mDirection.x, 0.2F);
	this->mPosition.y = Library::Lerp(this->mPosition.y, mDirection.y, 0.2F);
	mDestR->x = mPosition.x;
	mDestR->y = mPosition.y;

}

void Player::Fire()
{
}

void Player::Rendering()
{
	auto dirDeg = std::cos(Vector2::Dot(mDirection.normalized(), mPosition.normalized()));
	SDL_RendererFlip flip = dirDeg > 180 ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
	SDL_RenderCopyExF(mPlayerRenderer, mPlayerTex, mSrcR, mDestR, dirDeg, nullptr, flip);
}

void Player::Update()
{


	//destR.x = cnt;


}

void Player::Init(SDL_Renderer* playerRenderer)
{

	mPlayerRenderer = playerRenderer;
	mSrcR = new SDL_Rect{ .x=0, .y=0, .w=32, .h=32, };
	mDestR = new SDL_FRect{ .x=.0f, .y=.0f, .w=32.0f, .h=32.0f, };

	mDirection = Vector2(0.0f, 0.0f);
	mPosition = Vector2(0.0f, 0.0f);



	IMG_Init(IMG_INIT_PNG);
	const char* playerWhite = "assets/playerWhite.png";
	SDL_RWops* file = SDL_RWFromFile(playerWhite, "READ");

	SDL_Surface* tmpSurface = IMG_LoadPNG_RW(file);
	mPlayerTex = SDL_CreateTextureFromSurface(mPlayerRenderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);


}

Player::Player()
= default;













