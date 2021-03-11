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
		currentState.directionY += -moveModifier;
		std::cout << "up" << std::endl;
	}
	if (event.keysym.sym == mDown) {
		currentState.directionY += moveModifier;
		std::cout << "down" << std::endl;
	}
	if (event.keysym.sym == mLeft) {
		currentState.directionX += -moveModifier;
		std::cout << "left" << std::endl;
	}
	if (event.keysym.sym == mRight) {
		currentState.directionX += moveModifier;
		std::cout << "right" << std::endl;
	}
	if (event.keysym.sym == mSpace) {
		Fire();
		std::cout << "fire" << std::endl;
	}


	return 0;
}


int Player::Integrate(GameObject::State& state, time_point t)
{
	using namespace std::literals;

	state.velocityX += state.directionX + state.acceleration * dt / 1s;
	state.velocityY += state.directionY + state.acceleration * dt / 1s;


	return 0;
}

int Player::Move(time_point t)
{
	using namespace std::literals;
/*	mDirection.x = Library::clamp(mDirection.x, -1.f, 1.f);
	mDirection.y = Library::clamp(mDirection.y, -1.f, 1.f);*/
	Integrate(currentState, t);

/*	currentState.velocityX = Library::Lerp(currentState.velocityX, 0.0, dt / 1s);
	currentState.velocityY = Library::Lerp(currentState.velocityY, 0.0, dt / 1s);*/

	ScreenWrap();
	//previousState = currentState;
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
	double mAngle = 0;
	state.positionX += state.velocityX;
	state.positionY += state.velocityY;
	mDestRect.x = state.positionX;
	mDestRect.y = state.positionY;
	SDL_RenderCopyExF(mRenderer, mTexture, NULL, &mDestRect, mAngle, NULL, SDL_FLIP_HORIZONTAL);


	return 0;
}

Player::State Player::InterpolateState(double alpha) const
{
	State state = {};
	state.acceleration = currentState.acceleration * alpha + previousState.acceleration * (1 - alpha);
	state.velocityX = currentState.velocityX * alpha + previousState.velocityX * (1 - alpha);
	state.velocityY = currentState.velocityY * alpha + previousState.velocityY * (1 - alpha);

	return state;
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
	mSrcRect = { w/2, h/2, w/2, h/2 };
	mDestRect = { static_cast<float>(w/2), static_cast<float>(h/2), 64, 64 };
	currentState = { 10, 0, 0, static_cast<double>(w/2),static_cast<double>(h/2) };
	previousState = { 10, 0, 0, static_cast<double>(w/2),static_cast<double>(h/2) };
	IMG_Init(IMG_INIT_PNG);
	const char* playerWhite = "assets/playerWhite.png";

	mTexture = TextureManager::LoadTexture(playerWhite, mRenderer);

}













