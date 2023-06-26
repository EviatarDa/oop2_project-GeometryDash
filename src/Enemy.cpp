#pragma once
#include "Enemy.h"




Enemy::Enemy(b2World& world, const GameTextures texture, const sf::Vector2f location, const bool up,
	const GameAnimations animation, const GameTextures sprite_sheet)
	:MovingObject(world, texture, location),

	m_animation(Resources::instance().getAnimationData(animation), Right, m_object, sprite_sheet),
	m_up(up)
{
	//for correcting first direction
	swap();

	//attaching the object to the floor and rotate hin according to his location
	if (up)
	{
		m_attach = -1.f;
		m_object.rotate(180);
	}
	else
		m_attach = 1.f;

	//cancel the physisc gravity powers
	m_object_body->SetGravityScale(0.0f);
}

void Enemy::move()
{
	//move right acording to the gravity
	if(m_direction[Right])
		m_object_body->SetLinearVelocity({ ENEMY_MOVEMENT_SPEED, m_attach });
	else
		m_object_body->SetLinearVelocity({ -ENEMY_MOVEMENT_SPEED, m_attach });

	//moving the sprite after the body
	m_object.setPosition(SCALE * m_object_body->GetPosition().x, SCALE * m_object_body->GetPosition().y);
	const auto delta = m_clock.restart();
	m_animation.update(delta);
}

void Enemy::updateDirection()
{
	//swaping the direction from left to right
	if(m_swap)
	{
		m_direction[Right] = !m_direction[Right];
		m_direction[Left] = !m_direction[Left];
		if (m_up)
		{
			//up enemy animation
			if (m_direction[Right])
				m_animation.direction(Left);
			else
				m_animation.direction(Right);
		}
		else
		{
			//down enemy animation
			if (m_direction[Right])
				m_animation.direction(Right);
			else
				m_animation.direction(Left);
		}
		//no need to swap untill the next collision
		m_swap = false;
	}
}

void Enemy::swap()
{
	m_swap = true;
}



bool Enemy::m_registerit1 = Factory<MovingObject>::registerObject(ENEMY1_COLOR,
	[](b2World& world, sf::Vector2f location) -> std::unique_ptr<MovingObject> {
		return std::make_unique<Enemy>(world, Enemy1, location, false,
		Enemy1Animation, Enemy1SpriteSheet); }
);

bool Enemy::m_registerit2 = Factory<MovingObject>::registerObject(ENEMY1_UP_COLOR,
	[](b2World& world, sf::Vector2f location) -> std::unique_ptr<MovingObject> {
		return std::make_unique<Enemy>(world, Enemy1, location, true,
		Enemy1Animation, Enemy1SpriteSheet); }
);

bool Enemy::m_registerit3 = Factory<MovingObject>::registerObject(ENEMY2_COLOR,
	[](b2World& world, sf::Vector2f location) -> std::unique_ptr<MovingObject> {
		return std::make_unique<Enemy>(world, Enemy2, location, false,
		Enemy2Animation, Enemy2SpriteSheet); }
);

bool Enemy::m_registerit4 = Factory<MovingObject>::registerObject(ENEMY2_UP_COLOR,
	[](b2World& world, sf::Vector2f location) -> std::unique_ptr<MovingObject> {
		return std::make_unique<Enemy>(world, Enemy2, location, true,
		Enemy2Animation, Enemy2SpriteSheet); }
);