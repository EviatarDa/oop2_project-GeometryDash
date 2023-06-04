#include "ShipState.h"

void ShipState::move(Direction direction, b2Body* body)
{
    switch (direction)
    {
    case Up:
    {
        if (true)//to change
        {
            body->ApplyLinearImpulseToCenter(b2Vec2(0.0f, -SHIP_JUMP_FORCE), true);
        }
        break;
    }
    case Right:
    {
        float currentSpeed_y = body->GetLinearVelocity().y;
        body->SetLinearVelocity({ MOVEMENT_SPEED, currentSpeed_y });
        break;
    }
    case Left:
    {
        float currentSpeed_y = body->GetLinearVelocity().y;
        body->SetLinearVelocity({ -MOVEMENT_SPEED, currentSpeed_y });
        break;
    }

    case Stay:
    {
        float currentSpeed_y = body->GetLinearVelocity().y;
        body->SetLinearVelocity({ 0, currentSpeed_y });
        break;
    }

    default:
        break;
    }
}
