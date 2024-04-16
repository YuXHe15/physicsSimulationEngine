#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "PhysicsObject.hpp"
#include "VisualizationService.hpp"
#include <iostream>

VisualizationService::VisualizationService(unsigned int windowWidth, unsigned int windowHeight, const std::string& title) {
        window.create(sf::VideoMode(windowWidth, windowHeight), title);
        window.setFramerateLimit(60);
    }

void VisualizationService::addPhysicsObject(const std::string& id, const Sphere& obj, const sf::Color& color) {
        // Assume all objects are circles for simplicity
        std::cout << "Adding object with ID: " << id << std::endl;
        sf::CircleShape shape(obj.getRadius());
        shape.setFillColor(color);
        shape.setPosition(obj.x - obj.getRadius(), obj.y - obj.getRadius());
        shapes[id] = shape;
        std::cout << "Available IDs: ";
        for (const auto& pair : shapes) {
            std::cout << pair.first << " ";
        }
        std::cout << std::endl;
    }

void VisualizationService::updatePhysicsObject(const std::string& id, const Sphere& obj) {
        auto it = shapes.find(id);
        if (it != shapes.end()) {
            sf::Vector2f transformedPos = transformPosition(obj.x, obj.y, window.getSize().y);
            // Apply the transformed position to the shape
            it->second.setPosition(transformedPos.x - it->second.getRadius(), transformedPos.y - it->second.getRadius());
            std::cout << "Updating " << id << " to position: " << obj.x << ", " << obj.y << std::endl;
        }
    }

void VisualizationService::run() {
    if (!window.isOpen()) {
    std::cerr << "Failed to create window." << std::endl;
    return; // or handle the error appropriately
    }
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) window.close();
        }

        window.clear();
        for (const auto& pair : shapes) {
            window.draw(pair.second);
        }
        window.display();
    }
}

sf::Vector2f VisualizationService::transformPosition(float x, float y, float windowHeight) {
    // Invert the y-axis
    float transformedY = windowHeight - y;
    // Return the transformed position
    return sf::Vector2f(x, transformedY);
}

VisualizationService::~VisualizationService() {
    // Empty or cleanup code here
}
