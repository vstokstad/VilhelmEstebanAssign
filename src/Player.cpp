//
// Created by Vilhelm Stokstad on 2021-02-22.
//


#include "Player.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "include.h"
#include "Bullet.h"

int Player::HandleInput(SDL_KeyboardEvent event)
{
	if (event.type == SDL_KEYUP) {
		currentState.accelerationX = 0.0;
		currentState.accelerationY = 0.0;
	}
	else if (event.type == SDL_KEYDOWN || event.state == SDL_PRESSED) {
		switch (event.keysym.sym) {
		UP:
		case SDLK_UP:
			currentState.accelerationY -= 0.2;
			currentState.directionY += -1;
			std::cout << "up" << std::endl;
			break;
		DOWN:
		case SDLK_DOWN:
			currentState.accelerationY += 0.2;
			currentState.directionY += 1;

			std::cout << "down" << std::endl;
			break;
		LEFT:
		case SDLK_LEFT:
			currentState.accelerationX -= 0.2;
			currentState.directionX += -1;

			std::cout << "left" << std::endl;
			break;
		RIGHT:
		case SDLK_RIGHT:
			currentState.accelerationX += 0.2;
			currentState.directionX += 1;

			std::cout << "right" << std::endl;
			break;
		SHOOT:
		case SDLK_SPACE:
			Fire();
			std::cout << "fire" << std::endl;
			break;
		case SDLK_w:
			goto UP;
		case SDLK_s:
			goto DOWN;
		case SDLK_a:
			goto LEFT;
		case SDLK_d:
			goto RIGHT;

		};
	}


	return 0;
}


int Player::Move(time_point t)
{
	previousState = currentState;
	Integrate(currentState, t);


	return 0;
}

int Player::Render(double alpha)
{

	InterpolateState(alpha);
	SDL_RenderCopyExF(mRenderer, mTexture, NULL, &mDestRect, currentState.angle, NULL, flip);

	for (auto& b:bullets) {
		if (b.isActive) {
			b.Render(alpha);
		}
	}
	return 0;
}

int Player::Fire()
{

	if (bullets.empty()) {
		const char* bullet = "assets/player.png";
		SDL_Texture* bulletTexture = TextureManager::LoadTexture(bullet, mRenderer);
		bullets.emplace_back(mRenderer, this, bulletTexture);
	}
	for (auto& i : bullets) {

		if (i.isActive) continue;
		i.OnGetFired();
		return 0;
	}


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

	mDestRect = { 64, 64, 64, 64 };
	mCollider = { 64 - (64 / 4), 64 - (64 / 4), 48, 48 };
	currentState = { 0, 0, 0, 0, static_cast<double>(w / 2.0) - 32, static_cast<double>(h / 2.0) - 32, 0 , static_cast<double>(w/2.0)*-100};
	previousState = { 0, 0, 0, 0, static_cast<double>(w / 2.0) - 32, static_cast<double>(h / 2.0) - 32 , 0, static_cast<double>(w/2.0)*-100};

	IMG_Init(IMG_INIT_PNG);
	const char* playerWhite = "assets/playerWhite.png";
	const char* bullet = "assets/player.png";
	SDL_Texture* bulletTexture = TextureManager::LoadTexture(bullet, mRenderer);
	mTexture = TextureManager::LoadTexture(playerWhite, mRenderer);
	bullets.reserve(20);
	for (int i = 0; i < 10; ++i) {
		bullets.emplace_back(mRenderer, this, bulletTexture);
	}


}

int Player::CollisionDetection(SDL_Rect* sdlRect)
{

	if (SDL_HasIntersection(&mCollider, sdlRect) == SDL_TRUE) {
		std::cout << "collision" << std::endl;

		return 1;
	}
	return 0;
}

Player::~Player()
{


}













