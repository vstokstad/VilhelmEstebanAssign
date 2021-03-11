#pragma once

#include "include.h"



class TextureManager;

class GameObject
{
	friend class Player;

	friend class Asteroid;


	SDL_Texture* mTexture{};
	SDL_Renderer* mRenderer{};

	Vector2 mPosition{};
	Vector2 mDirection{};

	SDL_Rect mSrcRect{};
	SDL_Rect mDestRect{};


public:
	virtual int Update(double t, double dt) = 0;

	int ScreenWrap()
	{

		int o = mDestRect.w;
		int w = 1200*2;
		int h = 800*2;


		std::cout << mPosition.x << "< X Y >"<< mPosition.y << std::endl;

		if (mPosition.x > w+o) {
			mPosition.x = 0 - o;
		}
		else if (mPosition.x < 0-o) {
			mPosition.x = w+o;
		}
		if (mPosition.y > h+o) {
			mPosition.y = 0-o;
		}else if (mPosition.y < 0-o) {
			mPosition.y = h+o;
		}
		return 0;
	}

public:
	virtual int Render(double t, double fdt) = 0;
};


