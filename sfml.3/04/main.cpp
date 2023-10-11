#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <algorithm>

struct Eye
{
    sf::ConvexShape peach;
    sf::ConvexShape circle;
    sf::Vector2f position;
    float rotation = 0;
};

void updateeyeElements(Eye &eye);
sf::Vector2f toEuclidean(float radius, float angle);
float toDegrees(float radians);

void init(Eye &eye, sf::Vector2f eyePosition)
{
    constexpr int SET_POINT_EYE = 200;
    eye.position = eyePosition;

    eye.peach.setPointCount(SET_POINT_EYE);
    sf::Vector2f peachRadius = {150.f, 80.f};

    for (int pointNo = 0; pointNo < SET_POINT_EYE; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(SET_POINT_EYE);

        sf::Vector2f point = {
            peachRadius.x * std::sin(angle),
            peachRadius.y * std::cos(angle)};

        eye.peach.setPoint(pointNo, point);
    }
    eye.peach.setRotation(90);
    eye.peach.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));

    eye.circle.setPointCount(SET_POINT_EYE);
    sf::Vector2f circleRadius = {32.f, 21.f};

    for (int pointNo = 0; pointNo < SET_POINT_EYE; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(SET_POINT_EYE);

        sf::Vector2f point = {
            circleRadius.x * std::sin(angle),
            circleRadius.y * std::cos(angle)};

        eye.circle.setPoint(pointNo, point);
    }
    eye.circle.setFillColor(sf::Color(0x00, 0x00, 0x00));
    eye.circle.setRotation(90);
    updateeyeElements(eye);
}

sf::Vector2f toEuclidean(float radius, float angle)
{
    return {
        static_cast<float>(radius * cos(angle)),
        static_cast<float>(radius * sin(angle))};
}

float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

void updateeyeElements(Eye &eye)
{
    eye.peach.setPosition(eye.position);

    constexpr int SET_RADIUS_CIRCLE = 45;
    const sf::Vector2f circleOffset = toEuclidean(SET_RADIUS_CIRCLE, eye.rotation);
    eye.circle.setPosition(eye.position + circleOffset);
}

void onMouseMove(
    const sf::Event::MouseMoveEvent &event,
    sf::Vector2f &mousePosition)
{
    mousePosition = {float(event.x), float(event.y)};
}

void pollEvents(
    sf::RenderWindow &window,
    sf::Vector2f &mousePosition)
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
            onMouseMove(event.mouseMove, mousePosition);
            break;
        default:
            break;
        }
    }
}

void update(
    sf::Vector2f &mousePosition,
    Eye &leftEye,
    Eye &rightEye)
{
    const sf::Vector2f deltaLeft = mousePosition - leftEye.position;
    leftEye.rotation = atan2(deltaLeft.y, deltaLeft.x);
    const sf::Vector2f deltaRight = mousePosition - rightEye.position;
    rightEye.rotation = atan2(deltaRight.y, deltaRight.x);
    updateeyeElements(leftEye);
    updateeyeElements(rightEye);
}

void redrawFrame(
    sf::RenderWindow &window,
    Eye &leftEye,
    Eye &rightEye)
{
    window.clear();
    window.draw(leftEye.peach);
    window.draw(leftEye.circle);

    window.draw(rightEye.peach);
    window.draw(rightEye.circle);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Prints mouse events to terminal");

    Eye leftEye, rightEye;
    sf::Vector2f mousePosition;

    const sf::Vector2f SET_POS_LEFT_EYE = {300, 300};
    const sf::Vector2f SET_POS_RIGHT_EYE = {500, 300};
    init(leftEye, SET_POS_LEFT_EYE);
    init(rightEye, SET_POS_RIGHT_EYE);

    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(mousePosition, leftEye, rightEye);
        redrawFrame(window, leftEye, rightEye);
    }
    return 0;
}
