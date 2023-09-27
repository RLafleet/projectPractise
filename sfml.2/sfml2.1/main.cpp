#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

int main() {
    constexpr float BALL_SIZE = 40;
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}), "Wave Moving Ball");
    sf::Clock clock;
    const sf::Vector2f position = {10, 350};
    sf::CircleShape ball(BALL_SIZE);
    ball.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    sf::Vector2f speed = {100.f, 80.f};

    float totalTime = 0.0f; 
    constexpr float periodY = 2;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        const float deltaTime = clock.restart().asSeconds();
        totalTime += deltaTime;
        
        sf::Vector2f position = ball.getPosition();
        
        const float wavePhase = totalTime * float(2 * M_PI);

        if ((position.x + 2 * BALL_SIZE >= WINDOW_WIDTH) && (speed.x > 0)) {
            speed.x = -speed.x;
        }
        if ((position.x < 0) && (speed.x < 0)) {
            speed.x = -speed.x;
        }
        if ((position.y + 2 * BALL_SIZE >= WINDOW_HEIGHT) && (speed.y > 0)) {
            speed.y = -speed.y;
        }
        if ((position.y < 0) && (speed.y < 0)) {
            speed.y = -speed.y;
        }

        const float x = speed.x * deltaTime;
        const float y = speed.y * std::sin(wavePhase / periodY) * deltaTime;
        const sf::Vector2f offset = {x, y};

        ball.setPosition(position + offset);

        window.clear();
        window.draw(ball);
        window.display();
    }
}
