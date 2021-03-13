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
		currentState.directionX = 0.0;
		currentState.directionY = 0.0;
	}
	else if (event.type == SDL_KEYDOWN) {
		switch (event.keysym.sym) {
		case SDLK_UP:
			currentState.directionY += -.1;
			angle = 0.0;
			std::cout << "up" << std::endl;
			break;
		case SDLK_DOWN:
			currentState.directionY += .1;
			angle = 180.0;
			std::cout << "down" << std::endl;
			break;
		case SDLK_LEFT:
			currentState.directionX += -.1;
			angle = 270.0;
			std::cout << "left" << std::endl;
			break;
		case SDLK_RIGHT:
			currentState.directionX += .1;
			angle = 90.0;
			std::cout << "right" << std::endl;
			break;
		case SDLK_SPACE:
			Fire();
			std::cout << "fire" << std::endl;
			break;

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
	SDL_RenderCopyExF(mRenderer, mTexture, NULL, &mDestRect, angle, NULL, flip);

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
	currentState = { 0, 0, 0, 0, static_cast<double>(w / 2) - 32, static_cast<double>(h / 2) - 32 };
	previousState = { 0, 0, 0, 0, static_cast<double>(w / 2) - 32, static_cast<double>(h / 2) - 32 };

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













