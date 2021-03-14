#pragma once

#include "include.h"
#include "GameObject.h"
#include <array>

class TextureManager;


enum AsteroidSize
{
	BIG,
	MID,
	SMALL
};

class Asteroid : public virtual GameObject
{

public:


	explicit Asteroid(SDL_Renderer* renderer, AsteroidSize size);

	Asteroid() = delete;
	~Asteroid() = default;

	AsteroidSize size;


	int Render(double alpha) override;

	int Update(time_point t) override;


	int Split();

	int Move(time_point t);

	int Spawn();

	int randomNumberx = 0;
	int randomNumbery = 0;
	int velocity1 = 0;
	int velocity2 = 0;

};



