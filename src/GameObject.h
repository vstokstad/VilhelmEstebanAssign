#pragma once

#include "include.h"

using namespace std::literals;
auto constexpr dt = 1.0s / 60.0;
using duration = std::chrono::duration<double>;
using Clock = std::chrono::steady_clock;
using time_point = std::chrono::time_point<Clock, duration>;

class TextureManager;

class GameObject
{
	friend class Player;

	friend class Asteroid;

public:
	struct State
	{
		double accelerationX = 1.;
		double accelerationY = 1.;
		double velocityX = 0.;
		double velocityY = 0.;
		double positionX = 0.;
		double positionY = 0.;
		float directionX = 0.;
		float directionY = 0.;

	};

	SDL_Texture* mTexture{};
	SDL_Renderer* mRenderer{};
	const double speed = 500.;
	const float drag = .002f;
	double angle = 0.0;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	State currentState{};
	State previousState{};
	SDL_Rect mSrcRect{};
	SDL_FRect mDestRect{};
	int w = 0;
	int h = 0;


public:
	virtual int Update(time_point dt) = 0;


	virtual int Render(double alpha)
	{

		State state = InterpolateState(alpha);

		mDestRect.x = state.positionX;
		mDestRect.y = state.positionY;

		SDL_RenderCopyExF(mRenderer, mTexture, NULL, &mDestRect, angle, NULL, flip);

		return 0;
	}

	[[nodiscard]] State InterpolateState(double alpha) const
	{
		State state = currentState;

		state.accelerationX = currentState.accelerationX * alpha + previousState.accelerationX * (1 - alpha);
		state.accelerationY = currentState.accelerationY * alpha + previousState.accelerationY * (1 - alpha);
		state.velocityX = currentState.velocityX * alpha + previousState.velocityX * (1 - alpha);
		state.velocityY = currentState.velocityY * alpha + previousState.velocityY * (1 - alpha);
		state.positionX += state.velocityX * alpha + previousState.velocityX * (1 - alpha);
		state.positionY += state.velocityY * alpha + previousState.velocityY * (1 - alpha);
		ScreenWrap(state);
		return state;
	}

	int Integrate(State& state, time_point t)
	{
		using namespace std::literals;

		state.velocityX += state.directionX * ((speed + state.accelerationX) * dt / 1s);
		state.velocityY += state.directionY * ((speed + state.accelerationY) * dt / 1s);

		return 0;
	}

	int ScreenWrap(State& state) const
	{

		int o = (int)(mDestRect.w * 0.5);

		if (state.positionX > w + o) {
			state.positionX = 0 - o;
		}
		else if (state.positionX < 0.0 - o) {
			state.positionX = w + o;
		}
		if (state.positionY > h + o) {
			state.positionY = 0 - o;
		}
		else if (state.positionY < 0.0 - o) {
			state.positionX = h + o;
		}
		return 0;
	}
};



