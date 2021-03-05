//
// Created by Vilhelm Stokstad on 2021-02-22.
//



#pragma once
#include "include.h"
#include "RigidBody.cpp"
#include "TextureManager.h"

class Player : GameObject
{

public:

	Player();

	SDL_Keycode mUp = SDLK_UP;
	SDL_Keycode mDown = SDLK_DOWN;
	SDL_Keycode mLeft = SDLK_LEFT;
	SDL_Keycode mRight = SDLK_RIGHT;
	SDL_Keycode mSpace = SDLK_SPACE;

	Vector2 mPosition = Vector2(0,0);
	Vector2 mDirection = Vector2(0,0);

	RigidBody mRigidBody;
	SDL_Renderer* mPlayerRenderer = nullptr;

	SDL_Texture* mPlayerTex = nullptr;
	SDL_Rect mSrcR = {};
	SDL_Rect mDestR = {};


	int Update(double t, double dt);

	int Rendering(double t, double fdt);

	int HandleInput(SDL_KeyboardEvent event);

	int Fire();

	int Move(double t, double dt);

	int Init(SDL_Renderer* playerRenderer);

	int cnt = 0;
};



