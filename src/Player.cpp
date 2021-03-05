//
// Created by Vilhelm Stokstad on 2021-02-22.
//




#include "Player.h"
#include "TextureManager.h"

int Player::HandleInput(SDL_KeyboardEvent event)
{


	if (event.keysym.sym == mUp) {
		mDirection.y--;
		std::cout << "up" << std::endl;
	}
	if (event.keysym.sym == mDown) {
		mDirection.y++;
		std::cout << "down" << std::endl;
	}
	if (event.keysym.sym == mLeft) {
		mDirection.x--;
		std::cout << "left" << std::endl;
	}
	if (event.keysym.sym == mRight) {
		mDirection.x++;
		std::cout << "right" << std::endl;
	}
	if (event.keysym.sym == mSpace) {
		Fire();
		std::cout << "fire" << std::endl;
	};


	return 0;
}


int Player::Move(double t, double fdt)
{
	mPosition.x += mDirection.x * fdt;
	mPosition.y += mDirection.y * fdt;
	mRigidBody.UpdateRigidBody(mDirection, fdt);
	return 0;
}

int Player::Fire()
{
	return 0;
}

int Player::Rendering(double t, double fdt)
{
	mDestR.w = 64;
	mDestR.h = 64;
	mDestR.x = mPosition.x * fdt;
	mDestR.y = mPosition.y * fdt;

	SDL_RenderCopy(mPlayerRenderer, mPlayerTex, NULL, &mDestR);

	return 0;
}

int Player::Update(double t, double dt)
{
	Move(t, dt);

	return 0;

}

int Player::Init(SDL_Renderer* playerRenderer)
{
	mPlayerRenderer = playerRenderer;
	mSrcR = SDL_Rect{ mSrcR.w = 64, mSrcR.h = 64 };
	mDestR = SDL_Rect{ mDestR.w = 64, mDestR.h = 64 };
	mRigidBody = RigidBody(2.0, { mDestR.w, mDestR.h }, this->mPosition, this.mGameObject);
	IMG_Init(IMG_INIT_PNG);
	const char* playerWhite = "assets/playerWhite.png";
	//now using the Texture Manager
	mPlayerTex = TextureManager::LoadTexture(playerWhite, mPlayerRenderer);

	return 0;
}













