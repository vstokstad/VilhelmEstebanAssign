//
// Created by Vilhelm Stokstad on 2021-02-22.
//



#pragma once


#include "include.h"
#include "GameObject.h"



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
	State currentState={};
	State previousState={};


	int Render(double alpha) override;

	int Update(time_point t) override;

	int HandleInput(SDL_KeyboardEvent event);

	int Fire();

	int Move(time_point timePoint);


	[[nodiscard]] State InterpolateState(double alpha) const;


int Integrate(State& state, std::chrono::time_point<Clock, std::chrono::duration<double>>);
};



