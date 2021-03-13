#pragma once

#include "include.h"
#include "GameObject.h"


class TextureManager;

class Asteroid : public virtual GameObject
{

public:


	Asteroid() = delete;

	~Asteroid() = default;

	explicit Asteroid(SDL_Renderer* renderer);





	int Update(time_point t) override;

	int RandomNumb(float Max);

	int Split();

	int Move(time_point t);

	int Spawn();



};



