//
// Created by Vilhelm Stokstad on 2021-02-22.
//



#pragma once

#include "include.h"
#include "GameObject.h"
#include <vector>

class GameObject;

class Bullet;

class Player : public virtual GameObject
{

public:


	~Player();


	explicit Player(SDL_Renderer* renderer);

	std::vector<Bullet> bullets;
	SDL_Texture* bulletTexture;

	int Render(double alpha) override;

	int CollisionDetection(SDL_Rect* sdlRect);

	int Update(time_point t) override;

	int HandleInput(SDL_KeyboardEvent event);

	int Fire();

	int Move(time_point timePoint);

};



