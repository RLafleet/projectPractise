#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({820, 880}), "Full Name to abbreviation");

    window.clear();

    sf::ConvexShape roof;
    roof.setPosition({360, 150});
    roof.setFillColor(sf::Color(139, 0, 35));
    roof.setRotation(0);
    roof.setPointCount(4);
    roof.setPoint(0, {-130, 0});
    roof.setPoint(1, {+130, 0});
    roof.setPoint(2, {+320, 120});
    roof.setPoint(3, {-320, 120});
    window.draw(roof);

    sf::CircleShape smoke1(20);
    smoke1.setPosition({470, 70});
    smoke1.setFillColor(sf::Color(128, 128, 128));
    window.draw(smoke1);

    sf::CircleShape smoke2(24);
    smoke2.setPosition({475, 50});
    smoke2.setFillColor(sf::Color(128, 128, 128));
    window.draw(smoke2);

    sf::CircleShape smoke3(30);
    smoke3.setPosition({480, 30});
    smoke3.setFillColor(sf::Color(128, 128, 128));
    window.draw(smoke3);

    sf::CircleShape smoke4(33);
    smoke4.setPosition({490, 10});
    smoke4.setFillColor(sf::Color(128, 128, 128));
    window.draw(smoke4);

    sf::RectangleShape shape;
    shape.setSize({120, 40});
    shape.setRotation(90);
    shape.setPosition({500, 100});
    shape.setFillColor(sf::Color(64, 64, 64));
    window.draw(shape);

    sf::RectangleShape shape1;
    shape1.setSize({80, 40});
    shape1.setRotation(0);
    shape1.setPosition({440, 100});
    shape1.setFillColor(sf::Color(64, 64, 64));
    window.draw(shape1);

    sf::RectangleShape wall;
    wall.setSize({520, 300});
    wall.setPosition({100, 270});
    wall.setFillColor(sf::Color(139, 69, 19));
    window.draw(wall);

    sf::RectangleShape door;
    door.setSize({220, 90});
    door.setRotation(90);
    door.setPosition({250, 400});
    door.setFillColor(sf::Color::Black);
    window.draw(door);

    window.display();

    sf::sleep(sf::seconds(5));
}