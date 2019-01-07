#pragma once
#include "GlobalHeaders.h"





class PhysicsSource
{
public:
	PhysicsSource();
	~PhysicsSource();

	// Define the gravity vector.
	static b2Vec2 gravity;

	// Construct a world object, which will hold and simulate the rigid bodies.
	static b2World world;
};

