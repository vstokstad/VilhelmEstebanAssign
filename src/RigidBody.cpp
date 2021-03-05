//
// Created by Vilhelm Stokstad on 2021-03-04.
//


#include "RigidBody.h"
#include "GameObject.h"


RigidBody::RigidBody(float mass, Vector2 size, Vector2* parentPosition, GameObject* gameObject)
{
	mMass = mass;
	mSize = size;
	mPosition = parentPosition;
	mParentObject = gameObject;
};

void UpdateRigidBody(Vector2 withForce, double fdt)
{
	AddForce(withForce);
	UpdateVelocity(fdt);
	UpdatePosition(fdt);
}



void AddForce(Vector2 addedForce)
{
	mForce = addedForce;
}

Vector2 GetAcceleration()
{
	return { mForce.x / mMass,
	         mForce.y / mMass };
}

void UpdateVelocity(double fdt)
{
	mVelocity += GetAcceleration() * (float)fdt;
}

void UpdatePosition(double fdt)
{
	UpdateVelocity(fdt);
	*mPosition += mVelocity * (float)fdt;
}







