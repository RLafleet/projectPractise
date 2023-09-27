#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({820, 880}), "Full Name to abbreviation");

    window.clear();

    sf::RectangleShape shapeN1;
    shapeN1.setSize({220, 20});
    shapeN1.setRotation(90);
    shapeN1.setPosition({50, 10});
    shapeN1.setFillColor(sf::Color(0xFF, 0x0, 0x0));
    window.draw(shapeN1);

    sf::RectangleShape shapeN2;
    shapeN2.setSize({250, 3});
    shapeN2.setRotation(60);
    shapeN2.setPosition({50, 10});
    shapeN2.setFillColor(sf::Color(0xFF, 0x0, 0x0));
    window.draw(shapeN2);

    sf::RectangleShape shapeN3;
    shapeN3.setSize({220, 20});
    shapeN3.setRotation(90);
    shapeN3.setPosition({195, 10});
    shapeN3.setFillColor(sf::Color(0xFF, 0x0, 0x0));
    window.draw(shapeN3);

    sf::RectangleShape shape1;
    shape1.setSize({220, 20});
    shape1.setRotation(90);
    shape1.setPosition({250, 10});
    shape1.setFillColor(sf::Color(0xFF, 0x0, 0x0));
    window.draw(shape1);

    sf::RectangleShape shape2;
    shape2.setSize({150, 3});
    shape2.setRotation(60);
    shape2.setPosition({250, 10});
    shape2.setFillColor(sf::Color(0xFF, 0x0, 0x0));
    window.draw(shape2);

    sf::RectangleShape shape3;
    shape3.setSize({150, 3});
    shape3.setRotation(-60);
    shape3.setPosition({325, 139});
    shape3.setFillColor(sf::Color(0xFF, 0x0, 0x0));
    window.draw(shape3);

    sf::RectangleShape shape4;
    shape4.setSize({220, 20});
    shape4.setRotation(90);
    shape4.setPosition({420, 10});
    shape4.setFillColor(sf::Color(0xFF, 0x0, 0x0));
    window.draw(shape4);

    sf::RectangleShape shapeD1;
    shapeD1.setSize({220, 20});
    shapeD1.setRotation(90);
    shapeD1.setPosition({480, 10});
    shapeD1.setFillColor(sf::Color(0xFF, 0x0, 0x0));
    window.draw(shapeD1);

    sf::RectangleShape shapeD2;
    shapeD2.setSize({155, 3});
    shapeD2.setRotation(45);
    shapeD2.setPosition({480, 10});
    shapeD2.setFillColor(sf::Color(0xFF, 0x0, 0x0));
    window.draw(shapeD2);

    sf::RectangleShape shapeD3;
    shapeD3.setSize({155, 3});
    shapeD3.setRotation(-45);
    shapeD3.setPosition({478, 228});
    shapeD3.setFillColor(sf::Color(0xFF, 0x0, 0x0));
    window.draw(shapeD3);

    window.display();

    sf::sleep(sf::seconds(5));
}