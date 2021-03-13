#pragma once

#include <chrono>
#include "include.h"
#include <cmath>

using namespace std::literals;
auto constexpr dt = 1.0s / 60.0;
using duration = std::chrono::duration<double>;
using Clock = std::chrono::steady_clock;
using time_point = std::chrono::time_point<Clock, duration>;
struct State
{
	double accelerationX = 1.0;
	double accelerationY = 1.0;
	double velocityX = 0.0;
	double velocityY = 0.0;
	double positionX = 0.0;
	double positionY = 0.0;
	double directionX = 0.0;
	double directionY = 0.0;

};

class TextureManager;

class GameObject
{

public:


	SDL_Texture* mTexture{};
	SDL_Renderer* mRenderer{};
	double speed = 10.0;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	State currentState{};
	State previousState{};
	SDL_Rect mCollider{};
	SDL_FRect mDestRect{};
	double angle;
	int w = 0;
	int h = 0;


public:
	virtual int Update(time_point dt) = 0;


	virtual int Render(double alpha)
	{

		InterpolateState(alpha);


		SDL_RenderCopyExF(mRenderer, mTexture, NULL, &mDestRect, angle, NULL, flip);

		return 0;
	}

	void InterpolateState(double alpha)
	{

		/*currentState.accelerationX = currentState.accelerationX * alpha + previousState.accelerationX * (1 - alpha);
		currentState.accelerationY = currentState.accelerationY * alpha + previousState.accelerationY * (1 - alpha);*/

		currentState.velocityX = currentState.velocityX * alpha + previousState.velocityX * (1 - alpha);
		currentState.velocityY = currentState.velocityY * alpha + previousState.velocityY * (1 - alpha);
		currentState.positionX += currentState.velocityX * alpha + previousState.velocityX * (1 - alpha);
		currentState.positionY += currentState.velocityY * alpha + previousState.velocityY * (1 - alpha);
		mDestRect.x = (currentState.positionX+(mDestRect.w / 4)) * alpha + (previousState.positionX+(mDestRect.w / 4)) * (1 - alpha);
		mDestRect.y = (currentState.positionY+(mDestRect.h / 4)) * alpha + (previousState.positionY+(mDestRect.h / 4)) * (1 - alpha);
		mCollider.x = mDestRect.x+(mDestRect.w/4);
		mCollider.y = mDestRect.y+(mDestRect.h/4);

		ScreenWrap(&currentState);
	}

	int Integrate(State& state, std::chrono::time_point<Clock, std::chrono::duration<double>>)
	{
		using namespace std::literals;

		state.velocityX += speed * state.accelerationX * dt / 1s;
		state.velocityY += speed * state.accelerationY * dt / 1s;

		angle = (atan2(state.directionY, state.directionX) * 180 / 3.14519)*dt/1s;
		return 0;
	}

	int ScreenWrap(State* state) const
	{

		int o = mDestRect.w;

		if (state->positionX > w + o) {
			state->positionX = 0 - o;
		}
		else if (state->positionX < 0.0 - o) {
			state->positionX = w + o;
		}
		if (state->positionY > h + o) {
			state->positionY = 0 - o;
		}
		else if (state->positionY < 0.0 - o) {
			state->positionY = h + o;
		}
		return 0;
	}
};



