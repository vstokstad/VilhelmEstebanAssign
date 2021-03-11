#pragma once

#include "include.h"
#include "GameObject.h"


class TextureManager;
class RigidBody;

class Asteroid : public virtual GameObject
{

public:


	Asteroid() = delete;

	~Asteroid() = default;

	explicit Asteroid(SDL_Renderer* renderer);


	float randomDirX;
	float randomDirY;

	double angle = 0.0;
	float angleSpeed = 0.0;





	int Update(double t, double dt) override;

	int Render(double t, double fdt) override ;

	int Split();

	int Move();

	int Spawn();



};



