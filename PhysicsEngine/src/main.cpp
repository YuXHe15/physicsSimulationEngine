#include "VisualizationService.hpp"
#include "PhysicsObject.hpp"
#include <iostream>
#include <string>
#include <thread>  // For std::this_thread::sleep_for
#include <chrono>  // For std::chrono::milliseconds

void physicsUpdateLoop(Sphere& sphere, VisualizationService& visualizer, bool& running) {

    while (running) {
        // Update the physics object
        sphere.update(0.016f); // Update with a fixed time step of 16 milliseconds (roughly 60 updates per second)
        // sphere.display();  // For debugging purposes
        visualizer.updatePhysicsObject(sphere.name, sphere);

        // Optionally, limit the update rate for both physics and visualization
        std::this_thread::sleep_for(std::chrono::milliseconds(16)); // Roughly 60 updates per second

        // Check for a condition to stop the simulation
        // For demonstration purposes, we'll stop after some arbitrary movement
        if (sphere.y < -200) {
            running = false;
        }
    }
}

int main() {
    VisualizationService visualizer;

    // Example: Create a Sphere object
    Sphere sphere; // Position (100,100), radius 10
    sphere.setRadius(50);
    sphere.setDensity(2200);
    sphere.setPosition(400,300, 0);  // Initial position
    sphere.setAcceleration(0, -9.8, 0);  // Assuming no acceleration for simplicity
    sphere.setVelocity(20, 10, 0);  // Initial velocity
    // Add the sphere to the visualizer
    visualizer.addPhysicsObject(sphere.name, sphere, sf::Color::Red);

    bool running = true;
    std::thread physicsThread(physicsUpdateLoop, std::ref(sphere), std::ref(visualizer), std::ref(running));

    visualizer.run();  // This will block until the window is closed

    running = false;  // Ensure the physics loop stops if it hasn't already
    if (physicsThread.joinable()) {
        physicsThread.join();  // Wait for the physics thread to finish
    }
    return 0;
}
