//
// Created by Vilhelm Stokstad on 2021-02-22.
//




#include "Player.h"
#include "TextureManager.h"
#include "GameObject.h"

int Player::HandleInput(SDL_KeyboardEvent event)
{
	const double moveModifier = 1.1;

	if (event.keysym.sym == mUp) {
		currentState.directionY = -moveModifier;
		std::cout << "up" << std::endl;
	}
	if (event.keysym.sym == mDown) {
		currentState.directionY = moveModifier;
		std::cout << "down" << std::endl;
	}
	if (event.keysym.sym == mLeft) {
		currentState.directionX = -moveModifier;
		std::cout << "left" << std::endl;
	}
	if (event.keysym.sym == mRight) {
		currentState.directionX = moveModifier;
		std::cout << "right" << std::endl;
	}
	if (event.keysym.sym == mSpace) {
		Fire();
		std::cout << "fire" << std::endl;
	}


	return 0;
}


int Player::Move(time_point t)
{
	using namespace std::literals;

	Integrate(currentState, t);

	return 0;
}

int Player::Fire()
{
	return 0;
}

int Player::Render(double alpha)
{
	State state = InterpolateState(alpha);
	previousState = currentState;


	state.positionX += state.velocityX;
	state.positionY += state.velocityY;
	mDestRect.x = state.positionX;
	mDestRect.y = state.positionY;

	SDL_RenderCopyExF(mRenderer, mTexture, NULL, &mDestRect, angle, NULL, flip);

	return 0;
}


int Player::Update(time_point t)
{
	Move(t);

	return 0;

}


Player::Player(SDL_Renderer* renderer)
{

	SDL_GetRendererOutputSize(renderer, &w, &h);
	mRenderer = renderer;
	mSrcRect = { 64, 64, 64, 64 };
	mDestRect = { 64, 64, 64, 64 };
	currentState = { 10, 0, 0, 64, 64 };
	previousState = { 10, 0, 0, 64, 64 };

	IMG_Init(IMG_INIT_PNG);
	const char* playerWhite = "assets/playerWhite.png";

	mTexture = TextureManager::LoadTexture(playerWhite, mRenderer);

}













