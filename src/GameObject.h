#pragma once

#include "include.h"

extern const Vector2Int screenSize;
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

		float OffsetA = float(-100-mDestRect.w);
		
	//This makes him move twice?!
	//	mPosition = mPosition + mDirection;

		if (mPosition.x > (screenSize.x - OffsetA))
		{
			mPosition.x = OffsetA;
		}
		if (mPosition.y > (screenSize.y - OffsetA))
		{
			mPosition.y = OffsetA;
		}
		if (mPosition.x < OffsetA)
		{
			mPosition.x = (screenSize.x - OffsetA);
		}
		if (mPosition.y < OffsetA)
		{
			mPosition.y = (screenSize.y - OffsetA);
		}
		return 0;
	}

public:
	virtual int Render(double t, double fdt) = 0;
};


