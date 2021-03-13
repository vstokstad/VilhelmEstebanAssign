//
// Created by Vilhelm Stokstad on 2021-03-13.
//

#pragma once

#include "include.h"
#include "GameObject.h"

class Player;

class TextureManager;

class Bullet
{

public:
	Bullet() = delete;

	~Bullet() = default;

	explicit Bullet(SDL_Renderer* renderer, Player* mPlayer, SDL_Texture* texture);

	Player* mPlayer{};

	int mLifeTime = 200;

	int Move();

	int CollisionDetection(GameObject* gameObject);

	int OnHit(GameObject* gameObject);

	bool isActive = false;

	int Update();

	float directionX;
	float directionY;
	float speed = 10;
	SDL_Rect mDestRect = { 32, 32, 32, 32 };
	SDL_Renderer* mRenderer;
	SDL_Texture* mTexture;
	int w{};
	int h{};

	int OnGetFired();

	int ScreenWrap();

	int Render(double alpha);
};


