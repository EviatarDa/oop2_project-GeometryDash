#pragma once

#include "MyContactListener.h"


//======================collision functions======================:
//all the game collisions:


//prototype
void processCollision(GameObject& object1, GameObject& object2);

//--------------------------------------------------------------------


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
//--------------------------------------------------------------------

void playerGate(GameObject& player_object, GameObject& gate_object)
{
	Player& player = dynamic_cast<Player&>(player_object);
	Gate& gate = dynamic_cast<Gate&>(gate_object);

 	if(gate.isActive())
	{
	 	switch (gate.getType())
		{
		case Gate1:		player.setShipState();									break;
		case Gate2:		player.setBoxState();									break;
		case Gate3:		player.setGravity();	player.reverseGravity();		break;
		case Gate4:		player.setGravity();	player.reverseGravity();		break;
		case Gate5:		player.setWin();										break;
		}
		gate.inactive();
	}
}

void gatePlayer(GameObject& gate, GameObject& player)
{
	playerGate(player, gate);
}

//--------------------------------------------------------------------

void playerSpike(GameObject& player_object, GameObject& spike_object)
{
	Player& player = dynamic_cast<Player&>(player_object);

	player.setDead();
}

void spikePlayer(GameObject& spike, GameObject& player)
{
	playerSpike(player, spike);
}
//--------------------------------------------------------------------

void playerBrick(GameObject& player_object, GameObject& brick_object)
{
	Player& player = dynamic_cast<Player&>(player_object);
	Brick& brick = dynamic_cast<Brick&>(brick_object);

	//rectangle bricks will disapear for 5 sec
	if (brick.getType() == Rectangle)
	{
		brick.inactive();
	}
	player.collideBrick(brick.getType());
}

void brickPlayer(GameObject& brick, GameObject& player)
{
	playerBrick(player, brick);
}

//--------------------------------------------------------------------

void playerJumper(GameObject& player_object, GameObject& jumper_object)
{
	Player& player = dynamic_cast<Player&>(player_object);
	Jumper& jumper= dynamic_cast<Jumper&>(jumper_object);

	switch (jumper.getType())
	{
	case Jumper1:		player.hop(50.f);		break;
	case Jumper2:		player.hop(40.f);		break;
	}
}

void jumperPlayer(GameObject& jumper, GameObject& player)
{
	playerJumper(player, jumper);
}

//--------------------------------------------------------------------

void enemySpike(GameObject& enemy_object, GameObject& spike_object)
{
	Enemy& enemy = dynamic_cast<Enemy&>(enemy_object);
	//change enemy direction
	enemy.swap();

}


void spikeEnemy(GameObject& spike, GameObject& enemy)
{
	enemySpike(enemy, spike);
}

//--------------------------------------------------------------------

void playerEnemy(GameObject& player_object, GameObject& enemy_object)
{
	Player& player = dynamic_cast<Player&>(player_object);
	player.setDead();
}


void enemyPlayer(GameObject& enemy, GameObject& player)
{
	playerEnemy(player, enemy);
}

//--------------------------------------------------------------------

void enemyEnemy(GameObject& enemy1_object, GameObject& enemy2_object)
{
	Enemy& enemy1 = dynamic_cast<Enemy&>(enemy1_object);
	Enemy& enemy2 = dynamic_cast<Enemy&>(enemy2_object);
	
	enemy1.swap();
	enemy2.swap();
}



void MyContactListener::BeginContact(b2Contact* contact)
{
	//getting the fixture from the contact
	b2Fixture* fixtureA = contact->GetFixtureA();
	b2Fixture* fixtureB = contact->GetFixtureB();

	//getting the body from the fuxture
	b2Body* bodyA = fixtureA->GetBody();
	b2Body* bodyB = fixtureB->GetBody();

	//definding GameObject to process collision with
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


	//define the collision map
	HitMap initializeCollisionMap()
	{
		HitMap phm;
		phm[Key(typeid(Player), typeid(class Coin))] = &playerCoin;
		phm[Key(typeid(class Coin), typeid(Player))] = &coinPlayer;
		phm[Key(typeid(Player), typeid(Gate))] = &playerGate;
		phm[Key(typeid(Gate), typeid(Player))] = &gatePlayer;
		phm[Key(typeid(Player), typeid(Spike))] = &playerSpike;
		phm[Key(typeid(Spike), typeid(Player))] = &spikePlayer;
		phm[Key(typeid(Player), typeid(Brick))] = &playerBrick;
		phm[Key(typeid(Brick), typeid(Player))] = &brickPlayer;
		phm[Key(typeid(Player), typeid(Jumper))] = &playerJumper;
		phm[Key(typeid(Jumper), typeid(Player))] = &jumperPlayer;
		phm[Key(typeid(Enemy), typeid(Spike))] = &enemySpike;
		phm[Key(typeid(Spike), typeid(Enemy))] = &spikeEnemy;
		phm[Key(typeid(Player), typeid(Enemy))] = &playerEnemy;
		phm[Key(typeid(Enemy), typeid(Player))] = &enemyPlayer;
		phm[Key(typeid(Enemy), typeid(Enemy))] = &enemyEnemy;

		//...
		return phm;
	}

	//sercing for the collision
	HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2)
	{
		static HitMap collisionMap = initializeCollisionMap();
		auto mapEntry = collisionMap.find(std::make_pair(class1, class2));
		if (mapEntry == collisionMap.end())
		{
			return nullptr;
		}
		//the collision function
		return mapEntry->second;
	}

} // end namespace

void processCollision(GameObject& object1, GameObject& object2)
{
	//look for the collision and preform it accordingly to the types
	auto phf = lookup(typeid(object1), typeid(object2));
	if (!phf)
	{
		return;
	}
	else
		phf(object1, object2);
}