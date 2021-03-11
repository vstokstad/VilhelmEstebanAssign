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
	float speed = 0;




	int Update(time_point dt) override;

	int Render(double alpha) override;

	int Split();

	int Move();

	int Spawn();



};



