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

	Vector2 mPosition;
	Vector2 mDirection;

	SDL_Renderer* mPlayerRenderer = nullptr;


	SDL_Texture* mPlayerTex = nullptr;
	SDL_Rect* mSrcR = nullptr;
	SDL_FRect* mDestR = nullptr;


	void Update();

	void Rendering();

	void HandleInput(SDL_Event event);

	void Fire();

	void Move();

	void Init(SDL_Renderer* playerRenderer);


};



