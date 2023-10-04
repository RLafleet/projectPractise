#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

int main()
{
    constexpr int pointCount = 200;
    const sf::Vector2f initialEllipseRadius = {200.f, 80.f };

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Ellipse",
        sf::Style::Default, settings);

    sf::ConvexShape petail;
    petail.setPosition({400, 250});
    petail.setFillColor(sf::Color(0xFF, 0x09, 0x80));

    petail.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        float radius = 200 * std::sin(6 * angle);

        sf::Vector2f point = {
            radius * std::sin(angle),
            radius * std::cos(angle)
        };

        petail.setPoint(pointNo, point);
    }

    sf::Clock clock;
    sf::Vector2f speed = {80.f, 80.f};
    float totalTime = 0.0f;
    constexpr float periodY = 2;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        const float deltaTime = clock.restart().asSeconds();
        totalTime += deltaTime;
        const float wavePhase = totalTime * float(2 * M_PI);
        
        sf::Vector2f position = petail.getPosition();        

        const float x = speed.x * std::cos(wavePhase / periodY) * deltaTime;
        const float y = speed.y * std::sin(wavePhase / periodY) * deltaTime;
        const sf::Vector2f offset = {x, y};
            
        petail.setPosition(position + offset);

        window.clear();
        window.draw(petail);
        window.display();
    }

    return 0;
}
