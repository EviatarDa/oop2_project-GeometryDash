#include "Game.h"

int main()
{
    Game game;
    game.runMenu();
}

///** We need this to easily convert between pixel and real-world coordinates*/
//static const float SCALE = 30.f;
//
///** Create the base for the boxes to land */
//void CreateGround(b2World& World, float X, float Y);
//
///** Create the boxes */
//void CreateBox(b2World& World, int MouseX, int MouseY);
//
//int main()
//{
//    /** Prepare the window */
//    sf::RenderWindow Window(sf::VideoMode(800, 600, 32), "Test");
//    Window.setFramerateLimit(60);
//
//    /** Prepare the world */
//    b2Vec2 Gravity(0.f, 9.8f);
//    b2World World(Gravity);
//    CreateGround(World, 400.f, 500.f);
//
//    while (Window.isOpen())
//    {
//        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
//        {
//            int MouseX = sf::Mouse::getPosition(Window).x;
//            int MouseY = sf::Mouse::getPosition(Window).y;
//            CreateBox(World, MouseX, MouseY);
//        }
//        if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
//        {
//            for (b2Body* BodyIterator = World.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
//            {
//                BodyIterator->ApplyLinearImpulse(b2Vec2(0.0, -1.f), BodyIterator->GetWorldCenter(), false);
//                float horizontalForce = 5.f; // Adjust the force value as needed
//            }
//        }
//        World.Step(1 / 60.f, 8, 3);
//
//        Window.clear(sf::Color::White);
//        int BodyCount = 0;
//        for (b2Body* BodyIterator = World.GetBodyList(); BodyIterator != 0; BodyIterator = BodyIterator->GetNext())
//        {
//            if (BodyIterator->GetType() == b2_dynamicBody)
//            {
//                sf::RectangleShape rectangle;
//                rectangle.setSize(sf::Vector2f(25.f, 25.f));
//                rectangle.setOrigin(25,25);
//                rectangle.setFillColor(sf::Color::Green);
//                rectangle.setOutlineColor(sf::Color::Black);
//                rectangle.setOutlineThickness(2.0);
//                rectangle.setPosition(SCALE * BodyIterator->GetPosition().x, SCALE * BodyIterator->GetPosition().y);
//                rectangle.setRotation(BodyIterator->GetAngle() * 180 / b2_pi);
//                Window.draw(rectangle);
//                ++BodyCount;
//            }
//            else
//            {
//                sf::RectangleShape GroundRectangle;
//                GroundRectangle.setSize(sf::Vector2f(800,16));
//                GroundRectangle.setOrigin(400.f, 8.f);
//                GroundRectangle.setFillColor(sf::Color::Blue);
//                GroundRectangle.setPosition(BodyIterator->GetPosition().x * SCALE, BodyIterator->GetPosition().y * SCALE);
//                GroundRectangle.setRotation(180 / b2_pi * BodyIterator->GetAngle());
//                Window.draw(GroundRectangle);
//            }
//        }
//
//        Window.display();
//    }
//
//    return 0;
//}
//
//void CreateBox(b2World& World, int MouseX, int MouseY)
//{
//    b2BodyDef BodyDef;
//    BodyDef.position = b2Vec2(MouseX / SCALE, MouseY / SCALE);
//    BodyDef.type = b2_dynamicBody;
//    b2Body* Body = World.CreateBody(&BodyDef);
//
//    b2PolygonShape Shape;
//    Shape.SetAsBox((25.f / 2) / SCALE, (25.f / 2) / SCALE);
//    b2FixtureDef FixtureDef;
//    FixtureDef.density = 1.f;
//    FixtureDef.friction = 0.7f;
//    FixtureDef.shape = &Shape;
//    Body->CreateFixture(&FixtureDef);
//}
//
//void CreateGround(b2World& World, float X, float Y)
//{
//    b2BodyDef BodyDef;
//    BodyDef.position = b2Vec2(X / SCALE, Y / SCALE);
//    BodyDef.type = b2_staticBody;
//    b2Body* Body = World.CreateBody(&BodyDef);
//
//    b2PolygonShape Shape;
//    Shape.SetAsBox((800.f / 2) / SCALE, (16.f /4) / SCALE);
//    b2FixtureDef FixtureDef;
//    FixtureDef.density = 0.f;
//    FixtureDef.shape = &Shape;
//    Body->CreateFixture(&FixtureDef);
//}

//run game old:
// // Set up Box2D world
//b2Vec2 gravity(0.0f, 10.1f);
//b2World world(gravity);
//
//// Create ground body
//b2BodyDef groundBodyDef;
//groundBodyDef.position.Set(0.0f, m_window.getSize().y);
//b2Body* groundBody = world.CreateBody(&groundBodyDef);
//
//b2PolygonShape groundBox;
//groundBox.SetAsBox(m_window.getSize().x, 10.0f);
//groundBody->CreateFixture(&groundBox, 0.0f);
//
//// Create upper ground body (initially outside the visible area)
//b2BodyDef upperGroundBodyDef;
//upperGroundBodyDef.position.Set(0.0f, -10.0f);
//b2Body* upperGroundBody = world.CreateBody(&upperGroundBodyDef);
//
//b2PolygonShape upperGroundBox;
//upperGroundBox.SetAsBox(m_window.getSize().x, 10.0f);
//upperGroundBody->CreateFixture(&upperGroundBox, 0.0f);
//
//// Create rectangle body
//b2BodyDef rectangleBodyDef;
//rectangleBodyDef.type = b2_dynamicBody;
//rectangleBodyDef.position.Set(m_window.getSize().x / 2.0f, m_window.getSize().y - 50.0f); // Start position near the ground
//b2Body* rectangleBody = world.CreateBody(&rectangleBodyDef);
//
//b2PolygonShape rectangleShape;
//rectangleShape.SetAsBox(50.0f, 50.0f);
//
//b2FixtureDef rectangleFixtureDef;
//rectangleFixtureDef.shape = &rectangleShape;
//rectangleFixtureDef.density = 1.0f;
//rectangleFixtureDef.friction = 0.3f;
//rectangleBody->CreateFixture(&rectangleFixtureDef);
//
//// SFML Rectangle
//sf::RectangleShape rectangle(sf::Vector2f(100.0f, 100.0f));
//rectangle.setOrigin(50.0f, 50.0f);
//rectangle.setPosition(rectangleBody->GetPosition().x, rectangleBody->GetPosition().y);
//
//// Movement variables
//bool moveLeft = false;
//bool moveRight = false;
//bool gravityUpsideDown = false;
//
//// Start the main loop
//while (m_window.isOpen()) {
//    sf::Event event;
//    while (m_window.pollEvent(event)) {
//        if (event.type == sf::Event::Closed)
//            m_window.close();
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
//
//    // Apply horizontal velocity based on movement input
//    b2Vec2 velocity(0.0f, rectangleBody->GetLinearVelocity().y);
//    if (moveLeft)
//        velocity.x = -5.0f;
//    else if (moveRight)
//        velocity.x = 5.0f;
//    rectangleBody->SetLinearVelocity(velocity);
//
//    // Change gravity upside down if space is pressed
//    if (gravityUpsideDown)
//        world.SetGravity(b2Vec2(0.0f, -10.1f));
//    else
//        world.SetGravity(b2Vec2(0.0f, 10.1f));
//
//    world.Step(1.0f / 60.0f, 8, 3);
//
//    // Update SFML rectangle position
//    rectangle.setPosition(rectangleBody->GetPosition().x, rectangleBody->GetPosition().y);
//    rectangle.setRotation(rectangleBody->GetAngle() * 180 / b2_pi);
//
//    m_window.clear();
//    m_window.draw(rectangle);
//    //displayWorld(world);
//    m_window.display();
//}