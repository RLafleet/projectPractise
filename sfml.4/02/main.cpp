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

struct LaserPointer
{
    sf::Sprite pointerSprite;
    sf::Texture pointerTexture;
};

void initObject(Cat &cat)
{
    if (!cat.catTexture.loadFromFile("./02/cat.png"))
    {
        std::cerr << "Failed to load cat texture." << std::endl;
        return;
    }

    cat.catSprite.setTexture(cat.catTexture);
    cat.catSprite.setTextureRect(sf::IntRect(0, 0, cat.catTexture.getSize().x, cat.catTexture.getSize().y));
    cat.catSprite.setOrigin(cat.catTexture.getSize().x / 2.0f, cat.catTexture.getSize().y / 2.0f);
    cat.catSprite.setPosition(400, 300);
}

void initLaserPointer(LaserPointer &laserPointer)
{
    if (!laserPointer.pointerTexture.loadFromFile("./02/red_pointer.png"))
    {
        std::cerr << "Failed to load laser pointer texture." << std::endl;
        return;
    }

    laserPointer.pointerSprite.setTexture(laserPointer.pointerTexture);
    laserPointer.pointerSprite.setOrigin(laserPointer.pointerTexture.getSize().x / 2.0f, laserPointer.pointerTexture.getSize().y / 2.0f);
}

void onMouseMovePressed(const sf::Event::MouseButtonEvent &event, sf::Vector2f &mousePosition, bool &mouseMoveCheck)
{
    if (!mouseMoveCheck)
    {
        mouseMoveCheck = true;
    }
    mousePosition = {float(event.x), float(event.y)};
}

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition, bool &mouseMoveCheck, LaserPointer &laserPointer)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseButtonPressed:
            onMouseMovePressed(event.mouseButton, mousePosition, mouseMoveCheck);
            laserPointer.pointerSprite.setPosition(mousePosition);
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
    sf::Event event;
    if (mouseMoveCheck)
    {
        const sf::Vector2f delta = mousePosition - cat.catSprite.getPosition();

        if ((delta.x + delta.y) != 0)
        {
            const float magnitude = sqrt(delta.x * delta.x + delta.y * delta.y);
            const int catSPEED = 40;
            const sf::Vector2f direction = {delta.x / magnitude * catSPEED * deltaTime, delta.y / magnitude * catSPEED * deltaTime};
            cat.catSprite.setPosition(cat.catSprite.getPosition() + direction);
            const int DELTA_ROTATE = 3;

            if ((delta.x - DELTA_ROTATE) > 0 && cat.catRotate)
            {
                cat.catSprite.setScale(1, 1);
                cat.catRotate = false;
            }
            if ((delta.x + DELTA_ROTATE) < 0 && !cat.catRotate)
            {
                cat.catSprite.setScale(-1, 1);
                cat.catRotate = true;
            }
        }
    }
}

void redrawFrame(sf::RenderWindow &window, Cat &cat, LaserPointer &laserPointer)
{
    window.clear(sf::Color::White);
    window.draw(cat.catSprite);
    window.draw(laserPointer.pointerSprite);
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

    LaserPointer laserPointer;
    initObject(cat);
    initLaserPointer(laserPointer);

    while (window.isOpen())
    {
        pollEvents(window, mousePosition, mouseMoveCheck, laserPointer);
        update(mousePosition, cat, clock, totalTime, mouseMoveCheck);
        redrawFrame(window, cat, laserPointer);
    }

    return 0;
}
