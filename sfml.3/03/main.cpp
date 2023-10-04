#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <algorithm>

void init(sf::ConvexShape& pointer)
{
    pointer.setPointCount(3);
    pointer.setPoint(0, { 40, 0});
    pointer.setPoint(1, { -20, -20});
    pointer.setPoint(2, { -20, 20 });
    pointer.setPosition({ 400, 300 });
    pointer.setFillColor(sf::Color(0xFF, 0x80, 0x80));
}

float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

void onMouseMove(
    const sf::Event::MouseMoveEvent& event, 
    sf::Vector2f& mousePosition,
    bool& mouseMoveCheck)
{
    if (!mouseMoveCheck)
    {
        mouseMoveCheck = true;
    }
    mousePosition = { float(event.x), float(event.y) };
}

void pollEvents(
    sf::RenderWindow& window, 
    sf::Vector2f& mousePosition,
    bool& mouseMoveCheck)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseMoved:
            onMouseMove(event.mouseMove, mousePosition, mouseMoveCheck);
            break;  
        default:
            break;
        }
    }

}

void update(
    sf::Vector2f& mousePosition, 
    sf::ConvexShape& pointer, 
    sf::Clock& clock, 
    float& totalTime, 
    bool& mouseMoveCheck)
{
    const float deltaTime = clock.restart().asSeconds();
    totalTime += deltaTime;

    if (mouseMoveCheck)
    {
        const sf::Vector2f delta = mousePosition - pointer.getPosition();
        const float angle = atan2(delta.y, delta.x);
        const float maxRotationSpeed = 15.0f;

        float targetRotation = toDegrees(angle);

        float angleDiff = targetRotation - pointer.getRotation();
        if (angleDiff > 180.0f)
        {
            angleDiff -= 360.0f;
        }
        if (angleDiff <= -180.0f)
        {
            angleDiff += 360.0f;
        }

        float limitedRotationDiff = std::max(-maxRotationSpeed * deltaTime, std::min(maxRotationSpeed * deltaTime, angleDiff));

        pointer.rotate(limitedRotationDiff);
    }
}

void redrawFrame(
    sf::RenderWindow& window, 
    sf::ConvexShape& pointer)
{
    window.clear();
    window.draw(pointer);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;
    
    sf::Clock clock;
    float totalTime = 0.0f;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Prints mouse events to terminal");
    
    sf::ConvexShape pointer;
    sf::Vector2f mousePosition;
    bool mouseMoveCheck = false;
    init(pointer);
    while (window.isOpen())
    {
        pollEvents(window, mousePosition, mouseMoveCheck);
        update(mousePosition, pointer, clock, totalTime, mouseMoveCheck);
        redrawFrame(window, pointer);
    }
    return 0;
}
