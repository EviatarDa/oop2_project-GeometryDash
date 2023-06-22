#pragma once
#include "Enemy.h"




Enemy::Enemy(b2World& world, GameTextures texture, sf::Vector2f location, bool up,
	GameAnimations animation, GameTextures sprite_sheet)
	:MovingObject(world, texture, location),

	m_animation(Resources::instance().getAnimationData(animation), Right, m_object, sprite_sheet),
	m_up(up)
{
	//for correcting first direction
	swap();
	if (up)
	{
		m_attach = -1.f;
		m_object.rotate(180);
	}
	else
		m_attach = 1.f;

	m_object_body->SetGravityScale(0.0f);

}

void Enemy::move()
{
	if(m_direction[Right])
		m_object_body->SetLinearVelocity({ ENEMY_MOVEMENT_SPEED, m_attach });
	else
		m_object_body->SetLinearVelocity({ -ENEMY_MOVEMENT_SPEED, m_attach });

	m_object.setPosition(SCALE * m_object_body->GetPosition().x, SCALE * m_object_body->GetPosition().y);
	const auto delta = m_clock.restart();
	m_animation.update(delta);
}

void Enemy::updateDirection()
{
	if(m_swap)
	{
		m_direction[Right] = !m_direction[Right];
		m_direction[Left] = !m_direction[Left];
		if (m_up)
		{
			if (m_direction[Right])
				m_animation.direction(Left);
			else
				m_animation.direction(Right);
		}
		else
		{
			if (m_direction[Right])
				m_animation.direction(Right);
			else
				m_animation.direction(Left);
		}
		m_swap = false;
	}
}

void Enemy::swap()
{
	m_swap = true;
}



bool Enemy::m_registerit1 =  Factory::registerMovingObject(ENEMY1_COLOR,
	[](b2World& world, sf::Vector2f location) -> std::unique_ptr<MovingObject> {
		return std::make_unique<Enemy>(world, Enemy1, location, false,
		Enemy1Animation, Enemy1SpriteSheet); }
);

bool Enemy::m_registerit2 = Factory::registerMovingObject(ENEMY1_UP_COLOR,
	[](b2World& world, sf::Vector2f location) -> std::unique_ptr<MovingObject> {
		return std::make_unique<Enemy>(world, Enemy1, location, true,
		Enemy1Animation, Enemy1SpriteSheet); }
);

bool Enemy::m_registerit3 = Factory::registerMovingObject(ENEMY2_COLOR,
	[](b2World& world, sf::Vector2f location) -> std::unique_ptr<MovingObject> {
		return std::make_unique<Enemy>(world, Enemy2, location, false,
		Enemy2Animation, Enemy2SpriteSheet); }
);

bool Enemy::m_registerit4 = Factory::registerMovingObject(ENEMY2_UP_COLOR,
	[](b2World& world, sf::Vector2f location) -> std::unique_ptr<MovingObject> {
		return std::make_unique<Enemy>(world, Enemy2, location, true,
		Enemy2Animation, Enemy2SpriteSheet); }
);