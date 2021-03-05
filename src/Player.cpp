//
// Created by Vilhelm Stokstad on 2021-02-22.
//




#include "Player.h"


int Player::HandleInput(SDL_KeyboardEvent event)
{
	Vector2 addedMoveForce = Vector2();

	if (event.keysym.sym == mUp) {
		addedMoveForce.y-= 100;
		std::cout << "up" << std::endl;
	}
	if (event.keysym.sym == mDown) {
		addedMoveForce.y+= 100;
		std::cout << "down" << std::endl;
	}
	if (event.keysym.sym == mLeft) {
		addedMoveForce.x-=100;
		std::cout << "left" << std::endl;
	}
	if (event.keysym.sym == mRight) {
		addedMoveForce.x+=100;
		std::cout << "right" << std::endl;
	}
	if (event.keysym.sym == mSpace) {
		Fire();
		std::cout << "fire" << std::endl;
	};
std::cout << addedMoveForce.x << addedMoveForce.y << std::endl;
	mRigidBody.AddForce(addedMoveForce);

	return 0;
}


int Player::Move(double t, double dt)
{
	mPosition.x += mDirection.x;
	mPosition.y += mDirection.y;

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
	std::cout <<"x: "<< mRigidBody.position.x <<" y: " << mRigidBody.position.y <<std::endl;
	mDestR.x = mRigidBody.position.x;
	mDestR.y = mRigidBody.position.y;

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
	mSrcR = SDL_Rect{ mSrcR.w=64, mSrcR.h=64 };
	mDestR = SDL_Rect{ mDestR.w=64, mDestR.h=64 };

	IMG_Init(IMG_INIT_PNG);
	const char* playerWhite = "assets/playerWhite.png";
	//now using the Texture Manager
	mPlayerTex = TextureManager::LoadTexture(playerWhite, mPlayerRenderer);

	const char* playerWhite = "/assets/playerWhite.png";
	SDL_Surface* tmpSurface = IMG_Load(playerWhite);
	mPlayerTex = SDL_CreateTextureFromSurface(mPlayerRenderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);
	return 0;
}

Player::Player()
= default;













