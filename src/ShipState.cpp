#include "ShipState.h"

void ShipState::move(bool* direction, b2Body* body, bool&, b2Vec2 gravity, sf::Sprite& object)
{

    if(direction[Up])
    {
        //saving last vilocity and keep moving that way
        float currentSpeed_y = body->GetLinearVelocity().y;

        //ship always moving forward
        body->SetLinearVelocity({ PLAYER_MOVEMENT_SPEED, currentSpeed_y });

        //move up/down according to gravity
        if(gravity.y > 0)
            body->ApplyLinearImpulseToCenter(b2Vec2(0.0f, -SHIP_JUMP_FORCE), true);
        else
            body->ApplyLinearImpulseToCenter(b2Vec2(0.0f, SHIP_JUMP_FORCE), true);
    }
    else
    {
        //saving last vilocity and keep moving that way
        float currentSpeed_y = body->GetLinearVelocity().y;

        //ship always moving forward
        body->SetLinearVelocity({ PLAYER_MOVEMENT_SPEED, currentSpeed_y });
    }

    //move the sprite
    object.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);

}

void ShipState::collideBrick(bool& touching_ground, bool& alive)
{
    alive = false;
}

