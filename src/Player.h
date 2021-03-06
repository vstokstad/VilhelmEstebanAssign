//
// Created by Vilhelm Stokstad on 2021-02-22.
//



#pragma once

#include "include.h"
#include "GameObject.h"
#include <vector>


class Bullet;
class Asteroid;
class Player : public virtual GameObject
{

public:


	~Player();


	explicit Player(SDL_Renderer* renderer);

	std::vector<Bullet> bullets;
	SDL_Texture* bulletTexture;

	int Render(double alpha) override;

	int CollisionDetection(Asteroid* asteroid);

	int Update(time_point t) override;

	int HandleInput(SDL_KeyboardEvent event);

	int Fire();

	int Move(time_point timePoint);

};



