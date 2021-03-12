//
// Created by Vilhelm Stokstad on 2021-02-22.
//




#include "Player.h"
#include "TextureManager.h"
#include "GameObject.h"

int Player::HandleInput(SDL_KeyboardEvent event)
{
 if (event.type == SDL_KEYUP) {
		currentState.directionX = 0.0;
		currentState.directionY = 0.0;
	}else if (event.type==SDL_KEYDOWN) {
		switch (event.keysym.sym) {
		case SDLK_UP:
			currentState.directionY += -.1;
			std::cout << "up" << std::endl;
			break;
		case SDLK_DOWN:
			currentState.directionY += .1;
			std::cout << "down" << std::endl;
			break;
		case SDLK_LEFT:
			currentState.directionX += -.1;
			std::cout << "left" << std::endl;
			break;
		case SDLK_RIGHT:
			currentState.directionX += .1;
			std::cout << "right" << std::endl;
			break;
		case SDLK_SPACE:
			Fire();
			std::cout << "fire" << std::endl;
			break;
		};
	}

	currentState.directionX = Library::Lerp(currentState.directionX, 0., .1);
	currentState.directionY = Library::Lerp(currentState.directionY, 0., .1);
	std::cout << currentState.positionX << "<X  Y>" << currentState.positionY <<std::endl;
	return 0;
}


int Player::Move(time_point t)
{
	previousState = currentState;
	Integrate(currentState, t);
/*	currentState.velocityX = Library::Lerp((float)currentState.velocityX, 0.0, drag * dt / 1s);
	currentState.velocityY = Library::Lerp((float)currentState.velocityY, 0.0, drag * dt / 1s);*/
	return 0;
}

int Player::Fire()
{
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
	currentState = { 1, 0, 0, 0, static_cast<double>(w / 2) - 32, static_cast<double>(h / 2) - 32 };
	previousState = { 1, 0, 0, 0, static_cast<double>(w / 2) - 32, static_cast<double>(h / 2) - 32 };

	IMG_Init(IMG_INIT_PNG);
	const char* playerWhite = "assets/playerWhite.png";

	mTexture = TextureManager::LoadTexture(playerWhite, mRenderer);

}













