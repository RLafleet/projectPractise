#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <iostream>
#include <algorithm>

struct Cat
{
    sf::Sprite catSprite;
    sf::Texture catTexture;
    sf::Vector2f catPosition;
    bool catRotate;
};

void initObject(Cat &cat)
{
    if (!cat.catTexture.loadFromFile("./02/cat.png"))
    {
        std::cerr << "Failed to load texture!" << std::endl;
        return;
    }

    cat.catSprite.setTexture(cat.catTexture);
    cat.catSprite.setTextureRect(sf::IntRect(0, 0, cat.catTexture.getSize().x, cat.catTexture.getSize().y));
    cat.catSprite.setOrigin(cat.catTexture.getSize().x / 2.0f, cat.catTexture.getSize().y / 2.0f);
    cat.catSprite.setPosition(400, 300);
}

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition, bool &mouseMoveCheck)
{
    if (!mouseMoveCheck)
    {
        mouseMoveCheck = true;
    }
    mousePosition = {float(event.x), float(event.y)};
}

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition, bool &mouseMoveCheck)
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

void update(sf::Vector2f &mousePosition, Cat &cat, sf::Clock &clock, float &totalTime, bool &mouseMoveCheck)
{
    const float deltaTime = clock.restart().asSeconds();
    totalTime += deltaTime;

    if (mouseMoveCheck)
    {
        const sf::Vector2f delta = mousePosition - cat.catSprite.getPosition();

        if ((delta.x + delta.y) != 0)
        {
            const float magnitude = sqrt(delta.x * delta.x + delta.y * delta.y);
            const int catSPEED = 40;
            const sf::Vector2f direction = {delta.x / magnitude * catSPEED * deltaTime, delta.y / magnitude * catSPEED * deltaTime};
            cat.catSprite.setPosition(cat.catSprite.getPosition() + direction);

            if (delta.x > 0 && cat.catRotate)
            {
                cat.catSprite.setScale(1, 1);
                cat.catRotate = false;
            }
            if (delta.x < 0 && !cat.catRotate)
            {
                cat.catSprite.setScale(-1, 1);
                cat.catRotate = true;
            }
        }
    }
}

void redrawFrame(sf::RenderWindow &window, Cat &cat)
{
    window.clear(sf::Color::White);
    window.draw(cat.catSprite);
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
        "Prints mouse events to terminal",
        sf::Style::Default,
        settings);

    Cat cat;
    sf::Vector2f mousePosition;
    bool mouseMoveCheck = false;

    initObject(cat);
    while (window.isOpen())
    {
        pollEvents(window, mousePosition, mouseMoveCheck);
        update(mousePosition, cat, clock, totalTime, mouseMoveCheck);
        redrawFrame(window, cat);
    }
    return 0;
}
