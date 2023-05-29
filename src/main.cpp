//#include <SFML/Graphics.hpp>
//#include <Box2D/Box2D.h>

#include "Game.h"

int main()
{
    Game game;
    game.runMenu();
}

//int main() {
    //// Set up SFML window
    //sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Box2D Rectangle");

    //// Set up Box2D world
    //b2Vec2 gravity(0.0f, 0.1f);
    //b2World world(gravity);

    //// Create ground body
    //b2BodyDef groundBodyDef;
    //groundBodyDef.position.Set(0.0f, window.getSize().y);
    //b2Body* groundBody = world.CreateBody(&groundBodyDef);

    //b2PolygonShape groundBox;
    //groundBox.SetAsBox(window.getSize().x, 10.0f);
    //groundBody->CreateFixture(&groundBox, 0.0f);

    //// Create upper ground body (initially outside the visible area)
    //b2BodyDef upperGroundBodyDef;
    //upperGroundBodyDef.position.Set(0.0f, -10.0f);
    //b2Body* upperGroundBody = world.CreateBody(&upperGroundBodyDef);

    //b2PolygonShape upperGroundBox;
    //upperGroundBox.SetAsBox(window.getSize().x, 10.0f);
    //upperGroundBody->CreateFixture(&upperGroundBox, 0.0f);

    //// Create rectangle body
    //b2BodyDef rectangleBodyDef;
    //rectangleBodyDef.type = b2_dynamicBody;
    //rectangleBodyDef.position.Set(window.getSize().x / 2.0f, window.getSize().y - 50.0f); // Start position near the ground
    //b2Body* rectangleBody = world.CreateBody(&rectangleBodyDef);

    //b2PolygonShape rectangleShape;
    //rectangleShape.SetAsBox(50.0f, 50.0f);

    //b2FixtureDef rectangleFixtureDef;
    //rectangleFixtureDef.shape = &rectangleShape;
    //rectangleFixtureDef.density = 1.0f;
    //rectangleFixtureDef.friction = 0.3f;
    //rectangleBody->CreateFixture(&rectangleFixtureDef);

    //// SFML Rectangle
    //sf::RectangleShape rectangle(sf::Vector2f(100.0f, 100.0f));
    //rectangle.setOrigin(50.0f, 50.0f);
    //rectangle.setPosition(rectangleBody->GetPosition().x, rectangleBody->GetPosition().y);

    //// Movement variables
    //bool moveLeft = false;
    //bool moveRight = false;
    //bool gravityUpsideDown = false;

    //// Start the main loop
    //while (window.isOpen()) {
    //    sf::Event event;
    //    while (window.pollEvent(event)) {
    //        if (event.type == sf::Event::Closed)
    //            window.close();
    //        else if (event.type == sf::Event::KeyPressed) {
    //            if (event.key.code == sf::Keyboard::Left)
    //                moveLeft = true;
    //            else if (event.key.code == sf::Keyboard::Right)
    //                moveRight = true;
    //            else if (event.key.code == sf::Keyboard::Space)
    //                gravityUpsideDown = !gravityUpsideDown;
    //        }
    //        else if (event.type == sf::Event::KeyReleased) {
    //            if (event.key.code == sf::Keyboard::Left)
    //                moveLeft = false;
    //            else if (event.key.code == sf::Keyboard::Right)
    //                moveRight = false;
    //        }
    //    }

    //    // Apply horizontal velocity based on movement input
    //    b2Vec2 velocity(0.0f, rectangleBody->GetLinearVelocity().y);
    //    if (moveLeft)
    //        velocity.x = -5.0f;
    //    else if (moveRight)
    //        velocity.x = 5.0f;
    //    rectangleBody->SetLinearVelocity(velocity);

    //    // Change gravity upside down if space is pressed
    //    if (gravityUpsideDown)
    //        world.SetGravity(b2Vec2(0.0f, -0.1f));
    //    else
    //        world.SetGravity(b2Vec2(0.0f, 0.1f));

    //    world.Step(1.0f / 60.0f, 8, 3);

    //    // Update SFML rectangle position
    //    rectangle.setPosition(rectangleBody->GetPosition().x, rectangleBody->GetPosition().y);
    //    rectangle.setRotation(rectangleBody->GetAngle() * 180 / b2_pi);

    //    window.clear();
    //    window.draw(rectangle);
    //    window.display();
    //}

//    return 0;
//}
