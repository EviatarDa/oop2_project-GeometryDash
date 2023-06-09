#include "ShipState.h"

void ShipState::move(bool* direction, b2Body* body, bool&)
{
    if(direction[Up])
    {
        float currentSpeed_y = body->GetLinearVelocity().y;
        body->SetLinearVelocity({ MOVEMENT_SPEED, currentSpeed_y });
        body->ApplyLinearImpulseToCenter(b2Vec2(0.0f, -SHIP_JUMP_FORCE), true);
    }
    else
    {
        float currentSpeed_y = body->GetLinearVelocity().y;
        body->SetLinearVelocity({ MOVEMENT_SPEED, currentSpeed_y });
    }
}

