//
// Created by Vilhelm Stokstad on 2021-02-22.
//



#pragma once
#include "include.h"
#include "SDL_keycode.h"
#include "SDL_keyboard.h"


class Player
{

public:

	Player();

	SDL_Keycode mUp = SDLK_UP;
	SDL_Keycode mDown = SDLK_DOWN;
	SDL_Keycode mLeft = SDLK_LEFT;
	SDL_Keycode mRight = SDLK_RIGHT;
	SDL_Keycode mSpace = SDLK_SPACE;

	Vector2Int mPosition = Vector2Int(0,0);
	Vector2Int mDirection = Vector2Int(0,0);

	SDL_Renderer* mPlayerRenderer = nullptr;

	SDL_Texture* mPlayerTex = nullptr;
	SDL_Rect mSrcR = {};
	SDL_Rect mDestR = {};

	int Update();

	int Rendering();

	int HandleInput(SDL_Event event);

	int Fire();

	int Move();

	int Init(SDL_Renderer* playerRenderer);

	int cnt = 0;
};



