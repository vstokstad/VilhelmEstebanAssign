//
// Created by Vilhelm Stokstad on 2021-02-22.
//



#pragma once


#include "include.h"
#include "GameObject.h"



class Player : public virtual GameObject
{

public:

	~Player() = default;

	explicit Player(SDL_Renderer* renderer);

	int CollisionDetection(SDL_Rect* sdlRect);

	int Update(time_point t) override;

	int HandleInput(SDL_KeyboardEvent event);

	int Fire();

	int Move(time_point timePoint);






};



