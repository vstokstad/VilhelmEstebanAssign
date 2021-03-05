//
// Created by Vilhelm Stokstad on 2021-03-05.
//

#pragma once

#include "include.h"

class GameObject;

class RigidBody
{
	friend class GameObject;

public:
	GameObject* mParentObject{};
	Vector2 mPosition;
	Vector2 mSize;
	float mMass{};

	Vector2 mAcceleration;

	Vector2 mVelocity;

	[[nodiscard]] Vector2 GetAcceleration() const;

	void UpdateVelocity(double fdt);

	void AddForce(Vector2 addedForce);

	void UpdatePosition(double fdt);

	void UpdateRigidBody(Vector2 withForce, double fdt);


	RigidBody(float mass, Vector2 size, Vector2* parentPosition, GameObject* gameObject);

	RigidBody() = default;
};