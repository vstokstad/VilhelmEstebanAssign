//
// Created by Vilhelm Stokstad on 2021-03-13.
//

#pragma once

#include "include.h"

class Player;

class Asteroid;

class TextureManager;
class Bullet
{

public:
	Bullet() = delete;

	~Bullet() = default;

	explicit Bullet(SDL_Renderer* renderer, Player* mPlayer, SDL_Texture* texture);

	Player* mPlayer{};

	int mLifeTime = 500;

	int Move();

	int CollisionDetection(Asteroid* asteroid);

	int OnHit(Asteroid* asteroid);

	bool isActive = false;

	int Update();

	float directionX;
	float directionY;
	float speed = 3;
	SDL_Rect mDestRect = { 32, 32, 32, 32 };
	SDL_Renderer* mRenderer;
	SDL_Texture* mTexture;
	int w{};
	int h{};

	int OnGetFired();

	int ScreenWrap();

	int Render(double alpha);
};


