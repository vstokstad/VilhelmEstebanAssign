#pragma once

#include "include.h"

using namespace std::literals;
auto constexpr dt = 1.0s / 60.;
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
		double acceleration = 10;
		double velocityX = 0;
		double velocityY = 0;
		double positionX = 0;
		double positionY = 0;
		double directionX = 0;
		double directionY = 0;

	};

	SDL_Texture* mTexture{};
	SDL_Renderer* mRenderer{};

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

	virtual int Render(double alpha) = 0;

	[[nodiscard]] State InterpolateState(double alpha)
	{
		State state = {};
		state.acceleration = currentState.acceleration * alpha + previousState.acceleration * (1 - alpha);
		state.velocityX = currentState.velocityX * alpha + previousState.velocityX * (1 - alpha);
		state.velocityY = currentState.velocityY * alpha + previousState.velocityY * (1 - alpha);
		ScreenWrap(state);
		return state;
	}

	int Integrate(GameObject::State& state, time_point t)
	{
		using namespace std::literals;

		state.velocityX += state.directionX + state.acceleration * dt / 1s;
		state.velocityY += state.directionY + state.acceleration * dt / 1s;

		return 0;
	}

	int ScreenWrap(State& state) const
	{

		int o = (int)(mDestRect.w*0.5)+ (int)(mDestRect.h * 0.5);

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



