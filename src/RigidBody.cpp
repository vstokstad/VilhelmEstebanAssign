//
// Created by Vilhelm Stokstad on 2021-03-04.
//


#include "RigidBody.h"
#include "GameObject.h"


RigidBody::RigidBody(float mass, Vector2 size, Vector2* parentPosition, GameObject* gameObject)
{
	mMass = mass;
	mSize = size;
	mPosition = *parentPosition;
	mParentObject = gameObject;
};

void RigidBody::UpdateRigidBody(Vector2 withForce, double fdt)
{
	AddForce(withForce);
	UpdateVelocity(fdt);
	UpdatePosition(fdt);
}


void RigidBody::AddForce(Vector2 addedForce)
{
	mAcceleration += addedForce;
}

Vector2 RigidBody::GetAcceleration() const
{
	return { mAcceleration.x / mMass,
	         mAcceleration.y / mMass };
}

void RigidBody::UpdateVelocity(double fdt)
{
	mVelocity += GetAcceleration() * (float)fdt;
}

void RigidBody::UpdatePosition(double fdt)
{
	UpdateVelocity(fdt);
	mPosition +=  mVelocity * (float)fdt;
}







