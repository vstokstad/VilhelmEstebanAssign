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


	int randomDirX;
	int randomDirY;
	float mRotation;
	double angle = 0;
	float angleSpeed = 0;
	int screenBordersX = 0;
	int screenBordersY = 0;
	int speed = 0;

	RigidBody mRigidBody;


	int Update(double t, double dt) override;

	int Render(double t, double fdt) ;

	int Split();

	int Move();

	int Spawn(int w, int h);



};



