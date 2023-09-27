#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({220, 680}), "Traffic light");

    window.clear();

    sf::CircleShape shape1(100);
    shape1.setPosition({10, 20});
    shape1.setFillColor(sf::Color(0x0, 0xFF, 0x0));
    window.draw(shape1);

    sf::CircleShape shape2(100);
    shape2.setPosition({10, 240});
    shape2.setFillColor(sf::Color(0xFF, 0xFF, 0x0));
    window.draw(shape2);

    sf::CircleShape shape3(100);
    shape3.setPosition({10, 460});
    shape3.setFillColor(sf::Color(0xFF, 0x0, 0x0));
    window.draw(shape3);

    window.display();

    sf::sleep(sf::seconds(5));
}