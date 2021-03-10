#pragma once

#include "include.h"
#include "GameObject.h"
#include "RigidBody.h"

class TextureManager;
class RigidBody;

class Asteroid : public virtual GameObject
{

public:


	Asteroid() = delete;

	~Asteroid() = default;

	explicit Asteroid(SDL_Renderer* renderer);

	Vector2 mPosition;
	Vector2 mDirection;

	int randomDirX;
	int randomDirY;
	float mRotation;
	double angle = 0;
	float angleSpeed = 0;
	int screenBordersX = 0;
	int screenBordersY = 0;

	SDL_Renderer* mRenderer = nullptr;
	RigidBody mRigidBody;
	SDL_Texture* mTexture = nullptr;
	SDL_Rect* mSrcRect;
	SDL_Rect* mDestRect;

	int Update(double t, double dt) override;

	int Render(double t, double fdt) ;

	int Split();

	int Move();

	int Spawn(int w, int h);



};



