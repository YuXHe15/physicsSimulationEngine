#include "PhysicsObject.hpp"
#include "utils.hpp"
#include <iostream>
#include <string>
#include <cmath>



PhysicsObject::PhysicsObject(std::string name, float x, float y, float z, float vx, float vy, float vz) : name(name.empty() ? generateRandomName(5) : name), x(x), y(y), z(z), vx(vx), vy(vy), vz(vz) {};

PhysicsObject::~PhysicsObject() {};

void PhysicsObject::update(float detaTime) {
        updateVelocity(detaTime);
        updatePosition(detaTime);
};

void PhysicsObject::display() const {
        std::cout << "Name: " << name << std::endl;
        std::cout << "Position: (" << x << ", " << y << ", " << z << ")" << std::endl;
        std::cout << "Velocity: (" << vx << ", " << vy << ", " << vz << ")" << std::endl;
        if (ax.has_value() && ay.has_value() && az.has_value()) {
        std::cout << "Acceleration: (" << ax.value() << ", " << ay.value() << ", " << az.value() << ")" << std::endl;
        }
        if (mass.has_value()) {
            std::cout << "Mass: " << mass.value() << std::endl;
        }
        if (density.has_value()) {
            std::cout << "Density: " << density.value() << std::endl;
        }
        if (volume.has_value()) {
            std::cout << "Volume: " << volume.value() << std::endl;
        }
}

void PhysicsObject::setAcceleration(float ax, float ay, float az) {
    this->ax = ax;
    this->ay = ay;
    this->az = az;
}

void PhysicsObject::setPosition(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
}

void PhysicsObject::setVelocity(float vx, float vy, float vz) {
        this->vx = vx;
        this->vy = vy;
        this->vz = vz;
}

void PhysicsObject::setDensity(float newDensity) {
        density = newDensity;
        updateMassVolume();
}
void PhysicsObject::setVolume(float newVolume) {
        volume = newVolume;
        updateMassVolume();
}   

void PhysicsObject::updateMassVolume() {
        if (density && volume) {
            mass = density.value() * volume.value();
        }
}

void PhysicsObject::updateVelocity(float deltaTime) {
    if (ax.has_value()) vx += ax.value() * deltaTime;
    if (ay.has_value()) vy += ay.value() * deltaTime;
    if (az.has_value()) vz += az.value() * deltaTime;
}

void PhysicsObject::updatePosition(float detaTime) {
        x += vx * detaTime;
        y += vy * detaTime;
        z += vz * detaTime;
}

Sphere::Sphere(std::string name, float x, float y, float z, float vx, float vy, float vz, float radius) : PhysicsObject((name.empty() ? "Sphere_" + generateRandomName(5) : name), x, y, z, vx, vy, vz), radius(radius) {
    updateVolume();
}

Sphere::~Sphere() {};

void Sphere::setRadius(float newRadius) {
    radius = newRadius;
    updateVolume();
}

float Sphere::getRadius() const {
    return radius;
}

void Sphere::updateVolume() {
    volume = 4.0 / 3.0 * M_PI * std::pow(radius, 3);
}

Floor::Floor(std::string name, float x, float y, float z, float vx, float vy, float vz, float width, float height) : PhysicsObject((name.empty() ? "Floor_" + generateRandomName(5) : name), x, y, z, vx, vy, vz), width(width), height(height) {};
