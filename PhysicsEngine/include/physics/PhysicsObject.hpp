# ifndef PhysicsObject_HPP
# define PhysicsObject_HPP
# include <string>
# include "utils.hpp"
# include <optional>


class PhysicsObject {
    public:
        std::string name;
        float x, y, z;
        float vx, vy, vz;
        std::optional<float> mass, density, volume;
        std::optional<float> ax, ay, az;

        PhysicsObject(std::string name = "", float x = 0, float y = 0, float z = 0, float vx = 0, float vy = 0, float vz = 0);
        ~PhysicsObject();

        void setAcceleration(float ax, float ay, float az);

        void update(float detaTime);

        void display() const;

        void setPosition(float x, float y, float z);

        void setVelocity(float vx, float vy, float vz);

        void setDensity(float newDensity);

        void setVolume(float newVolume);
    private:
        void updateMassVolume();

        void updateVelocity(float detaTime);

        void updatePosition(float detaTime);
};

class Sphere : public PhysicsObject {
    public:
        Sphere(std::string name = "", float x = 0, float y = 0, float z = 0, float vx = 0, float vy = 0, float vz = 0, float radius = 1);
        ~Sphere();

        void setRadius(float newRadius);

        float getRadius() const;
    private:
        float radius;
        void updateVolume();
};

class Floor : public PhysicsObject {
    public:
        Floor(std::string name = "", float x = 0, float y = 0, float z = 0, float vx = 0, float vy = 0, float vz = 0, float width = 1, float height = 1);
        ~Floor();

        void setWidth(float newWidth);

        void setHeight(float newHeight);

        float getWidth() const;

        float getHeight() const;
    private:
        float width, height;
        void updateVolume();
};

# endif