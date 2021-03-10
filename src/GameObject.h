#pragma once

#include "include.h"


class TextureManager;

class GameObject
{
friend class Player;
friend class Asteroid;
friend class RigidBody;



	SDL_Texture* mTexture{};
	SDL_Renderer* mRenderer{};

	Vector2 mPosition;
	SDL_Rect mSrcRect{};
	SDL_Rect mDestRect{};
public:
	virtual int Update(double t, double dt) = 0;


public:
	virtual int Render(double t, double fdt) = 0;
};


