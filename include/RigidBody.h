//
// Created by Vilhelm Stokstad on 2021-03-04.
//

#pragma once

#include "include.h"

class RigidBody
{
public:
	RigidBody() = delete;

	explicit RigidBody(float mass)
	{
		this->mass = mass;

	}

	Vector2 position={ 0.0, 0.0 };
private:
	float mass = 0.5f;
	Vector2 force = { 1.0, 1.0 };

	Vector2 velocity={ 0.0, 0.0 };

	Vector2 GetAcceleration() const
	{
		return force / mass;
	}

	void UpdateVelocity(double dt)
	{
		velocity += GetAcceleration() * (float)dt;
	}

public:

	void UpdatePosition(double dt)
	{
		UpdateVelocity(dt);
		position += velocity * (float)dt;
	}

	void AddForce(Vector2 addedForce)
	{
		force += addedForce;
	}

};





