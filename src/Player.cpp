//
// Created by Vilhelm Stokstad on 2021-02-22.
//




#include "Player.h"
#include "TextureManager.h"
#include "GameObject.h"

int Player::HandleInput(SDL_KeyboardEvent event)
{
	const float moveModifier = 2.f;

	if (event.keysym.sym == mUp) {
		mDirection.y += -moveModifier;
		std::cout << "up" << std::endl;
	}
	if (event.keysym.sym == mDown) {
		mDirection.y += moveModifier;
		std::cout << "down" << std::endl;
	}
	if (event.keysym.sym == mLeft) {
		mDirection.x += -moveModifier;
		std::cout << "left" << std::endl;
	}
	if (event.keysym.sym == mRight) {
		mDirection.x += moveModifier;
		std::cout << "right" << std::endl;
	}
	if (event.keysym.sym == mSpace) {
		Fire();
		std::cout << "fire" << std::endl;
	}


	return 0;
}


int Player::Move(double t, double dt)
{
	mDirection.x =Library::clamp(mDirection.x, -5.f, 5.f);
	mDirection.y =Library::clamp(mDirection.y, -5.f, 5.f);


	mDirection.x = mDirection.x;
	mDirection.y = mDirection.y;
	mPosition.x += mDirection.x;
	mPosition.y += mDirection.y;

	mDirection.x = Library::Lerp(mDirection.x, 0.0, 0.005);
	mDirection.y = Library::Lerp(mDirection.y, 0.0, 0.005);
ScreenWrap();
	return 0;
}

int Player::Fire()
{
	return 0;
}

int Player::Render(double t, double fdt)
{

	double mAngle = 0;

	mDestRect.x = mPosition.x;
	mDestRect.y = mPosition.y;
	SDL_RenderCopyEx(mRenderer, mTexture, NULL, &mDestRect, mAngle, NULL, SDL_FLIP_NONE);


	return 0;
}

int Player::Update(double t, double dt)
{
	Move(t, dt);

	return 0;

}


Player::Player(SDL_Renderer* renderer)
{
	mSrcRect = SDL_Rect{ 64, 64, 64, 64 };
	mDestRect = SDL_Rect{ 64, 64, 64, 64 };
	mPosition = Vector2((64), (64));
	mDirection = Vector2(0, 0);
	mRenderer = renderer;

	IMG_Init(IMG_INIT_PNG);
	const char* playerWhite = "assets/playerWhite.png";

	mTexture = TextureManager::LoadTexture(playerWhite, mRenderer);

}













