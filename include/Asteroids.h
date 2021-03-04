#pragma once

#include "include.h"

class Asteroid
{

public:

	Asteroid();


	Vector2Int mPosition = Vector2Int(0, 0);
	Vector2Int mDirection = Vector2Int(0, 0);

	SDL_Renderer* mAsteroidRenderer = nullptr;

	SDL_Texture* mAsteroidTex = nullptr;
	SDL_Rect mSrcR = {};
	SDL_Rect mDestR = {};

	int Update();

	int Rendering();

	int Split();

	int Init(SDL_Renderer* mAsteroidRenderer);

};

