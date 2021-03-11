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






	float speed = 5;




	int Update(time_point t) override;

	int Render(double alpha) override;

	int Split();

	int Move(time_point t);

	int Spawn();



};



