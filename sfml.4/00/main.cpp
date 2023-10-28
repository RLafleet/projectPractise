#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <algorithm>

void init(sf::ConvexShape &pointer)
{
    pointer.setPosition({400, 300});

    pointer.setPointCount(7);
    pointer.setPoint(0, {-20, 0});
    pointer.setPoint(1, {-20, -40});
    pointer.setPoint(2, {40, 20});
    pointer.setPoint(3, {-20, 80});
    pointer.setPoint(4, {-20, 40});
    pointer.setPoint(5, {-80, 40});
    pointer.setPoint(6, {-80, 0});

    pointer.setFillColor(sf::Color(0xFF, 0xFF, 0));
    pointer.setOutlineColor(sf::Color::Black);
    pointer.setOutlineThickness(3.f);
}

void redrawFrame(
    sf::RenderWindow &window,
    sf::ConvexShape &pointer)
{
    window.clear(sf::Color::White);
    window.draw(pointer);
    window.display();
}

void pollEvents(
    sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        default:
            break;
        }
    }
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

    sf::ConvexShape pointer;
    init(pointer);
    while (window.isOpen())
    {
        pollEvents(window);
        redrawFrame(window, pointer);
    }
    return 0;
}
