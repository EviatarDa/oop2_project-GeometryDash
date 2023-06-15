#include "Enemy.h"
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
	//m_object.setRotation(m_object_body->GetAngle() * 180 / b2_pi);//
	const auto delta = m_clock.restart();
	m_animation.update(delta);
}

void Enemy::swap()
{
	m_direction[Right] = !m_direction[Right];
	m_direction[Left] = !m_direction[Left];
	if(m_up)
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

}




