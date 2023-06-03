#include "ShipState.h"

void ShipState::move(Direction direction, b2Body* body)
{
    switch (direction)
    {
    case Up:
    {
        float currentSpeed_x = body->GetLinearVelocity().x;
        body->SetLinearVelocity({ currentSpeed_x, MOVEMENT_SPEED }); //tochange movement speed
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
