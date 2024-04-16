# ifndef ENGINE_HPP
# define ENGINE_HPP
#include "PhysicsObject.hpp"


class PhysicsEngine {
    public:
        PhysicsEngine();
        ~PhysicsEngine();
        void addObject(const PhysicsObject& object);
        void removeObject(const std::string& name);
        void update(float deltaTime);
    private:
        std::vector<PhysicsObject> objects;
        void respondToCollision(PhysicsObject& obj1, PhysicsObject& obj2);

};

struct GridCell {
    std::vector<PhysicsObject*> objects;
};

class SpatialGrid {
    public:
        SpatialGrid(float width, float height, float depth, float cellSize);

        ~SpatialGrid();

        int hashPositionToIndex(float x, float y, float z);

        void addObject(PhysicsObject* object);

        void removeObject(PhysicsObject* object);
        std::vector<std::pair<PhysicsObject*, PhysicsObject*>> getPotentialCollisions();

    private:
        std::vector<GridCell> mCells;
        float mColumns, mRows, mLayers, cellSize;
};

#endif