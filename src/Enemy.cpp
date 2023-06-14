#include "Enemy.h"
#pragma once

#include "Enemy.h"

Enemy::Enemy(b2World& world, GameTextures texture, sf::Vector2f location, bool up)
	:MovingObject(world, texture, location),
	m_animation(Resources::instance().getAnimationData(EnemyAnimation), Right, m_object)
{
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
	//m_object.setRotation(m_object_body->GetAngle() * 180 / b2_pi);//
	const auto delta = m_clock.restart();
	m_animation.update(delta);
}

void Enemy::swap()
{
	m_direction[Right] = !m_direction[Right];
	m_direction[Left] = !m_direction[Left];
	if(m_direction[Right])
		m_animation.direction(Right);
	else
		m_animation.direction(Left);

}




