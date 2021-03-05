//
// Created by Vilhelm Stokstad on 2021-02-22.
//




#include "Player.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "RigidBody.h"

int Player::HandleInput(SDL_KeyboardEvent event)
{
	const float moveModifier = 50.f;

	if (event.keysym.sym == mUp) {
		mDirection.y = -moveModifier;
		std::cout << "up" << std::endl;
	}
	if (event.keysym.sym == mDown) {
		mDirection.y = moveModifier;
		std::cout << "down" << std::endl;
	}
	if (event.keysym.sym == mLeft) {
		mDirection.x = -moveModifier;
		std::cout << "left" << std::endl;
	}
	if (event.keysym.sym == mRight) {
		mDirection.x = moveModifier;
		std::cout << "right" << std::endl;
	}
	if (event.keysym.sym == mSpace) {
		Fire();
		std::cout << "fire" << std::endl;
	};


	return 0;
}


int Player::Move(double t, double dt)
{
	mPosition = mPosition+mDirection*dt;


	return 0;
}

int Player::Fire()
{
	return 0;
}

int Player::Render(double t, double fdt)
{
	mRigidBody.AddForce(mDirection);

	mRigidBody.UpdatePosition(fdt);
	mDestRect.w = 64;
	mDestRect.h = 64;
	mDestRect.x = (int)mPosition.x;
	mDestRect.y = (int)mPosition.y;

	SDL_RenderCopy(mRenderer, mPlayerTex, NULL, &mDestRect);
	return 0;
}

int Player::Update(double t, double dt)
{
	Move(t, dt);

	return 0;

}


Player::Player(SDL_Renderer* renderer) : mRenderer(renderer)
{
	mRenderer = renderer;
	mSrcRect = SDL_Rect{ mSrcRect.w = 64, mSrcRect.h = 64 };
	mDestRect = SDL_Rect{ mDestRect.w = 64, mDestRect.h = 64 };
	mRigidBody = RigidBody(0, Vector2(), &this->mPosition, this);
	mDirection = Vector2(0.f, 0.f);
	mPosition = mDirection*0.01f;
	if (IMG_Init(IMG_INIT_PNG) == 0) {
		std::cout << "could not init SDL_image in Player constructor: " << SDL_GetError() << std::endl;
	}
	const char* playerWhite = "assets/playerWhite.png";
	//now using the Texture Manager
	mPlayerTex = TextureManager::LoadTexture(playerWhite, mRenderer);

}













