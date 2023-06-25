#include "BoxState.h"

void BoxState::move(bool* direction, b2Body* body, bool& touching_ground, const b2Vec2 gravity, sf::Sprite& object)
{
    if(direction[Up])
    {
        if (touching_ground)
        {
            //to avoid "icetower" jumps
            body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));

            if(gravity.y > 0)
                body->ApplyLinearImpulseToCenter(b2Vec2(0.0f, -BOX_JUMP_FORCE), true);
            else
                body->ApplyLinearImpulseToCenter(b2Vec2(0.0f, BOX_JUMP_FORCE), true);

            direction[Up] = false;
            touching_ground = false;
        }
    }
    if(direction[Right])
    {
        float currentSpeed_y = body->GetLinearVelocity().y;
        body->SetLinearVelocity({ PLAYER_MOVEMENT_SPEED, currentSpeed_y });
    }
    if(direction[Left])
    {
        float currentSpeed_y = body->GetLinearVelocity().y;
        body->SetLinearVelocity({ -PLAYER_MOVEMENT_SPEED, currentSpeed_y });
    }
    if(direction[Stay])
    {
        float currentSpeed_y = body->GetLinearVelocity().y;
        body->SetLinearVelocity({ 0, currentSpeed_y });
    }
    
    object.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);
    object.setRotation(body->GetAngle() * 180 / b2_pi);

}

void BoxState::collideBrick(bool& touching_ground, bool& alive)
{
    touching_ground = true;
}
