#ifndef VISUALIZATIONSERVICE_HPP
#define VISUALIZATIONSERVICE_HPP

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include "PhysicsObject.hpp" // Include the header for your PhysicsObject class

class VisualizationService {
public:
    VisualizationService(unsigned int windowWidth = 800, unsigned int windowHeight = 600, const std::string& title = "Physics Simulation");
    ~VisualizationService();

    // Disallow copy construction and assignment to ensure unique service instance
    VisualizationService(const VisualizationService&) = delete;
    VisualizationService& operator=(const VisualizationService&) = delete;

    // Add a physics object to be visualized
    void addPhysicsObject(const std::string& id, const Sphere& obj, const sf::Color& color = sf::Color::White);

    // Update the visual representation of a physics object
    void updatePhysicsObject(const std::string& id, const Sphere& obj);

    // Run the visualization loop
    void run();

private:
    sf::RenderWindow window;
    std::unordered_map<std::string, sf::CircleShape> shapes; // Maps IDs to SFML shapes
    sf::Vector2f transformPosition(float x, float y, float windowHeight);

    // Utility functions
    void handleEvents();
    void render();
};

#endif // VISUALIZATIONSERVICE_HPP
