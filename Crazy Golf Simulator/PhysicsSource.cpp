#include "PhysicsSource.h"



PhysicsSource::PhysicsSource()
{
}


PhysicsSource::~PhysicsSource()
{
}
// Define the gravity vector.
b2Vec2 PhysicsSource::gravity(3.0f, -2.f);

// Construct a world object, which will hold and simulate the rigid bodies.
b2World PhysicsSource::world(gravity);