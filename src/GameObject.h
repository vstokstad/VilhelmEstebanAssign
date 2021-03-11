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

	Vector2 mPosition{};
	Vector2 mDirection{};

	SDL_Rect mSrcRect{};
	SDL_FRect mDestRect{};
	int w = 0;
	int h = 0;


public:
	virtual int Update(time_point dt) = 0;

	virtual int Render(double alpha) = 0;

	int ScreenWrap()
	{

		int o = mDestRect.w;

		if (mPosition.x > w + o) {
			mPosition.x = 0 - o;
		}
		else if (mPosition.x < 0 - o) {
			mPosition.x = w + o;
		}
		if (mPosition.y > h + o) {
			mPosition.y = 0 - o;
		}
		else if (mPosition.y < 0 - o) {
			mPosition.y = h + o;
		}
		return 0;
	}
};



