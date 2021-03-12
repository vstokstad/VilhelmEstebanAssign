//
// Created by Vilhelm Stokstad on 2021-02-22.
//




#include "Player.h"
#include "TextureManager.h"
#include "GameObject.h"

int Player::HandleInput(SDL_KeyboardEvent event)
{


	if (event.keysym.sym == mUp) {
		currentState.directionY += -.1;
		std::cout << "up" << std::endl;
	}
	if (event.keysym.sym == mDown) {
		currentState.directionY += .1;
		std::cout << "down" << std::endl;
	}
	if (event.keysym.sym == mLeft) {
		currentState.directionX += -.1;
		std::cout << "left" << std::endl;
	}
	if (event.keysym.sym == mRight) {
		currentState.directionX += .1;
		std::cout << "right" << std::endl;
	}
	if (event.keysym.sym == mSpace) {
		Fire();
		std::cout << "fire" << std::endl;
	}
	currentState.directionX = Library::clamp(currentState.directionX, -1., 1.);
	currentState.directionY = Library::clamp(currentState.directionY, -1., 1.);

	return 0;
}


int Player::Move(time_point t)
{
	previousState = currentState;
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


	mDestRect.x = state.positionX;
	mDestRect.y = state.positionY;

	SDL_RenderCopyExF(mRenderer, mTexture, NULL, &mDestRect, angle, NULL, flip);
	currentState.velocityX = Library::Lerp((float)currentState.velocityX, 0.0, drag * dt / 1s);
	currentState.velocityY = Library::Lerp((float)currentState.velocityY, 0.0, drag * dt / 1s);
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













