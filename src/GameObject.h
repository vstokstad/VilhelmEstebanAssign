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
	double accelerationX = 0.0;
	double accelerationY = 0.0;
	double velocityX = 0.0;
	double velocityY = 0.0;
	double positionX = 0.0;
	double positionY = 0.0;
	double directionX = 0.0;
	double directionY = 0.0;
	double angle = 0.0;
};

class TextureManager;


class GameObject
{

public:
	bool hasChildren = false;

	bool isActive = false;
	SDL_Texture* mTexture{};
	SDL_Renderer* mRenderer{};
	double speed = 10.0;
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	State currentState{};
	State previousState{};
	SDL_Rect mCollider{};
	SDL_FRect mDestRect{};
	int w = 0;
	int h = 0;


public:
	virtual int Update(time_point dt) = 0;


	virtual int Render(double alpha){
		if (isActive) {
			InterpolateState(alpha);
			SDL_RenderCopyExF(mRenderer, mTexture, NULL, &mDestRect, currentState.angle, NULL, flip);
		}


		return 0;
	};

	void InterpolateState(double alpha)
	{

		/*currentState.accelerationX = currentState.accelerationX * alpha + previousState.accelerationX * (1 - alpha);
		currentState.accelerationY = currentState.accelerationY * alpha + previousState.accelerationY * (1 - alpha);*/

		currentState.velocityX = currentState.velocityX * alpha + previousState.velocityX * (1 - alpha);
		currentState.velocityY = currentState.velocityY * alpha + previousState.velocityY * (1 - alpha);
		currentState.positionX += currentState.velocityX * alpha + previousState.velocityX * (1 - alpha);
		currentState.positionY += currentState.velocityY * alpha + previousState.velocityY * (1 - alpha);
		currentState.angle = currentState.angle * alpha + previousState.angle * (1 - alpha);
		mDestRect.x = (currentState.positionX - (mDestRect.w / 2)) * alpha +
		              (previousState.positionX - (mDestRect.w / 2)) * (1 - alpha);
		mDestRect.y = (currentState.positionY - (mDestRect.h / 2)) * alpha +
		              (previousState.positionY - (mDestRect.h / 2)) * (1 - alpha);
		mCollider.x = mDestRect.x + (mDestRect.w / 4);
		mCollider.y = mDestRect.y + (mDestRect.h / 4);

		ScreenWrap(&currentState);
	}

	int Integrate(State& state, std::chrono::time_point<Clock, std::chrono::duration<double>>)
	{

		using namespace std::literals;
		state.velocityX += (speed * state.accelerationX) * dt / 1s;
		state.velocityY += (speed * state.accelerationY) * dt / 1s;
		state.directionX = (state.velocityX * (h / 2.0));
		state.directionY = (state.velocityY * (w / 2.0));
		state.angle = (atan2(state.directionY, state.directionX) * (180 / 3.14)) + 90;
		return 0;
	}

	int ScreenWrap(State* state) const
	{

		int offset = mDestRect.w;

		if (state->positionX > w + offset) {
			state->positionX = 0 - offset;
		}
		else if (state->positionX < 0.0 - offset) {
			state->positionX = w + offset;
		}
		if (state->positionY > h + offset) {
			state->positionY = 0 - offset;
		}
		else if (state->positionY < 0.0 - offset) {
			state->positionY = h + offset;
		}
		return 0;
	}
};





