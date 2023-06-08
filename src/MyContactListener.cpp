#pragma once

#include "MyContactListener.h"


//=====functions-colision====:

void processCollision(GameObject& object1, GameObject& object2);

void playerCoin(GameObject& player_object, GameObject& coin_object)
{
	Player& player = dynamic_cast<Player&>(player_object);
	class Coin& coin = dynamic_cast<class Coin&>(coin_object);
	player.increasePoints();
	coin.setDelete();
}

void coinPlayer(GameObject& coin, GameObject& player)
{
	playerCoin(player, coin);
}

void MyContactListener::BeginContact(b2Contact* contact)
{
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();
	b2Body* bodyA = fixtureA->GetBody();
	b2Body* bodyB = fixtureB->GetBody();

	GameObject* objectA = reinterpret_cast<GameObject*>(bodyA->GetUserData().pointer);
	GameObject* objectB = reinterpret_cast<GameObject*>(bodyB->GetUserData().pointer);

	processCollision(*objectA, *objectB);
}

namespace // anonymous namespace � the standard way to make function "static"
{

	using HitFunctionPtr = std::function<void(GameObject&, GameObject&)>;
	// typedef void (*HitFunctionPtr)(GameObject&, GameObject&);
	using Key = std::pair<std::type_index, std::type_index>;
	// std::unordered_map is better, but it requires defining good hash function for pair
	using HitMap = std::map<Key, HitFunctionPtr>;



	HitMap initializeCollisionMap()
	{
		HitMap phm;
		phm[Key(typeid(Player), typeid(class Coin))] = &playerCoin;
		phm[Key(typeid(class Coin), typeid(Player))] = &coinPlayer;
		//phm[Key(typeid(SpaceShip), typeid(SpaceStation))] = &shipStation;
		//phm[Key(typeid(Asteroid), typeid(SpaceStation))] = &asteroidStation;
		//phm[Key(typeid(SpaceShip), typeid(SpaceShip))] = &shipShip;
		//phm[Key(typeid(Asteroid), typeid(SpaceShip))] = &asteroidShip;
		//phm[Key(typeid(SpaceStation), typeid(SpaceShip))] = &stationShip;
		//phm[Key(typeid(SpaceStation), typeid(Asteroid))] = &stationAsteroid;
		//...
		return phm;
	}


	HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2)
	{
		static HitMap collisionMap = initializeCollisionMap();
		auto mapEntry = collisionMap.find(std::make_pair(class1, class2));
		if (mapEntry == collisionMap.end())
		{
			return nullptr;
		}
		return mapEntry->second;
	}

} // end namespace

void processCollision(GameObject& object1, GameObject& object2)
{
	auto phf = lookup(typeid(object1), typeid(object2));
	if (!phf)
	{
		//throw std::runtime_error(std::string("Unknown collision of ") + typeid(object1).name()//////TODO fix
		//	+ " and " + typeid(object2).name());
	}
	else
		phf(object1, object2);
}