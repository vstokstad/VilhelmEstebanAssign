//
// Created by Vilhelm Stokstad on 2021-02-22.
//




#include "include.h"


class Player
{

public:

	Player();

	SDL_KeyCode mUp = SDLK_UP;
	SDL_KeyCode mDown = SDLK_DOWN;
	SDL_KeyCode mLeft = SDLK_LEFT;
	SDL_KeyCode mRight = SDLK_RIGHT;
	SDL_KeyCode mSpace = SDLK_SPACE;

	Vector2 mPosition = Vector2(0,0);
	Vector2 mDirection = Vector2(0,0);

	SDL_Renderer* mPlayerRenderer = nullptr;


	SDL_Texture* mPlayerTex = nullptr;
	SDL_Rect* mSrcR = nullptr;
	SDL_FRect* mDestR = nullptr;


	int Update();

	int Rendering();

	int HandleInput(SDL_Event event);

	int Fire();

	int Move();

	int Init(SDL_Renderer* playerRenderer);


};



