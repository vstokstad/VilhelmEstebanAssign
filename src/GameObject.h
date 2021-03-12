#pragma once

#include "include.h"
#include <chrono>

using namespace std::literals;
auto constexpr dt = 1.0s / 60.0;
using duration = std::chrono::duration<double>;
using Clock = std::chrono::steady_clock;
using time_point = std::chrono::time_point<Clock, duration>;
struct State
{
	double accelerationX = 1.;
	double accelerationY = 1.;
	double velocityX = 0.;
	double velocityY = 0.;
	double positionX = 0.;
	double positionY = 0.;
	double directionX = 0.;
	double directionY = 0.;

};

class TextureManager;

class GameObject
{
	friend class Player;

	friend class Asteroid;

public:


	SDL_Texture* mTexture{};
	SDL_Renderer* mRenderer{};
	double speed = 100.;
	const double drag = 5.;
	double angle = 0.0;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	State currentState;
	State previousState;
	SDL_Rect mSrcRect{};

	SDL_FRect mDestRect{};
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
		mDestRect.x = currentState.positionX * alpha + previousState.positionX * (1 - alpha);
		mDestRect.y = currentState.positionY * alpha + previousState.positionY * (1 - alpha);
		ScreenWrap(&currentState);
	}

	int Integrate(State& state, std::chrono::time_point<Clock, std::chrono::duration<double>>)
	{
		using namespace std::literals;

		state.velocityX += state.directionX * (speed + state.accelerationX) * dt / 1s;
		state.velocityY += state.directionY * (speed + state.accelerationY) * dt / 1s;

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



