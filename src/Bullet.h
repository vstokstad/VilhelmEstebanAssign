//
// Created by Vilhelm Stokstad on 2021-03-13.
//

#pragma once

#include "include.h"
#include "GameObject.h"

class Player;

class TextureManager;

class Bullet : public virtual GameObject
{

public:
	Bullet() = delete;

	~Bullet() = default;

	explicit Bullet(SDL_Renderer* renderer, Player* mPlayer);

	Player* mPlayer{};

	int mLifeTime = 20000;

	int CollisionDetection(GameObject* gameObject);

	int OnHit(GameObject* gameObject);

	bool isActive = false;

	int Update(time_point t) override;

	int Move(time_point t);


	int OnGetFired();
};


