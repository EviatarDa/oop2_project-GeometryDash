#include "MyContactListener.h"

void MyContactListener::BeginContact(b2Contact* contact)
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();
	b2Body* bodyA = fixtureA->GetBody();
	b2Body* bodyB = fixtureB->GetBody();

	GameObject* a = reinterpret_cast<GameObject*>(bodyA->GetUserData().pointer);
	GameObject* b = reinterpret_cast<GameObject*>(bodyB->GetUserData().pointer);

	//processCollision(*a, *b);
}
