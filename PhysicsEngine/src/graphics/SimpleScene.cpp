#include "SimpleScene.hpp"
#include <SFML/Graphics.hpp>

void drawSimpleScene() {
    // Create a render window
    sf::RenderWindow window(sf::VideoMode(640, 480), "Simple Scene");

    // Create some shapes
    sf::CircleShape circle(50); // Circle with radius 50
    circle.setFillColor(sf::Color::Green);
    circle.setPosition(100, 100); // Position the circle

    sf::RectangleShape rectangle(sf::Vector2f(120, 50)); // Rectangle 120x50
    rectangle.setFillColor(sf::Color::Blue);
    rectangle.setPosition(300, 200); // Position the rectangle

    // Main loop
    while (window.isOpen()) {
        // Event processing
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear screen
        window.clear();

        // Draw shapes
        window.draw(circle);
        window.draw(rectangle);

        // Update the window
        window.display();
    }
}
