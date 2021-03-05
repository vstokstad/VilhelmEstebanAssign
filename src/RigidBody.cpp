//
// Created by Vilhelm Stokstad on 2021-03-04.
//


#include "include.h"
#include "GameObject.h"

class RigidBody
{
public:

	explicit RigidBody(float mass, Vector2 size, Vector2* parentPosition, GameObject* gameObject);

	Vector2* position;
	Vector2 size;
private:
	GameObject* parentObject{};
	float mass;

	Vector2 force = { 1.0, 1.0 };

	Vector2 velocity = { 0.0, 0.0 };

	[[nodiscard]] Vector2 GetAcceleration() const
	{
		return { force.x / mass,
		         force.y / mass };
	}

	void UpdateVelocity(double fdt)
	{
		velocity += GetAcceleration() * (float)fdt;
	}

	void UpdatePosition(double fdt)
	{
		UpdateVelocity(fdt);
		*position += velocity * (float)fdt;
	}

public:


	void UpdateRigidBody(Vector2 withForce, double fdt)
	{
		AddForce(withForce);
		UpdateVelocity(fdt);
		UpdatePosition(fdt);
	}

	void AddForce(Vector2 addedForce)
	{
		force += addedForce;
	}

};

RigidBody::RigidBody(float mass, Vector2 size, Vector2* parentPosition, GameObject* gameObject)
		: size(size),
		  mass(mass),
		  position(parentPosition),
		  parentObject(gameObject)
{
	this->mass = mass;
	this->size = size;
	position = parentPosition;
	parentObject = gameObject;
}





