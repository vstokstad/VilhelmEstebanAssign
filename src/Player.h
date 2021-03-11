//
// Created by Vilhelm Stokstad on 2021-02-22.
//



#pragma once


#include "include.h"
#include "GameObject.h"


class RigidBody;

class Player : public virtual GameObject

{

public:


	~Player() = default;

	explicit Player(SDL_Renderer* renderer);


	SDL_Keycode mUp = SDLK_UP;
	SDL_Keycode mDown = SDLK_DOWN;
	SDL_Keycode mLeft = SDLK_LEFT;
	SDL_Keycode mRight = SDLK_RIGHT;
	SDL_Keycode mSpace = SDLK_SPACE;

	int Render(double t, double fdt) override;

	int Update(double t, double dt) override;

	int HandleInput(SDL_KeyboardEvent event);

	int Fire();

	int Move(double t, double dt);




};



