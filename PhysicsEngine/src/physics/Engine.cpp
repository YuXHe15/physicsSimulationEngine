#include "Engine.hpp"
#include "PhysicsObject.hpp"

void PhysicsEngine::addObject(const PhysicsObject& object) {
    objects.push_back(object);
}

void PhysicsEngine::removeObject(const std::string& name) {
    auto it = std::find_if(objects.begin(), objects.end(), [&name](const PhysicsObject& obj) {
        return obj.name == name;
    });
    if (it != objects.end()) {
        objects.erase(it);
    }
}

void PhysicsEngine::update(float deltaTime) {
    for (PhysicsObject& obj : objects) {
        obj.update(deltaTime);
    }
    // Check for collisions
}

SpatialGrid::SpatialGrid(float width, float height, float depth, float cellSize): cellSize(cellSize) {
    mColumns = static_cast<int>(std::ceil(width / cellSize));
    mRows = static_cast<int>(std::ceil(height / cellSize));
    mLayers = static_cast<int>(std::ceil(depth / cellSize));
    mCells.resize(mColumns);
};

SpatialGrid::~SpatialGrid() {
    mCells.clear();
};

int SpatialGrid::hashPositionToIndex(float x, float y, float z) {
    int column = static_cast<int>(x / cellSize);
    int row = static_cast<int>(y / cellSize);
    int layer = static_cast<int>(z / cellSize);
    return column + row * mColumns + layer * mColumns * mRows;
};

void SpatialGrid::addObject(PhysicsObject* object) {
    int index = hashPositionToIndex(object->x, object->y, object->z);
    mCells[index].objects.push_back(object);
};

void SpatialGrid::removeObject(PhysicsObject* object) {
    int index = hashPositionToIndex(object->x, object->y, object->z);
    auto it = std::find(mCells[index].objects.begin(), mCells[index].objects.end(), object);
    if (it != mCells[index].objects.end()) {
        mCells[index].objects.erase(it);
    }
};

std::vector<std::pair<PhysicsObject*, PhysicsObject*>> SpatialGrid::getPotentialCollisions() {
    std::vector<std::pair<PhysicsObject*, PhysicsObject*>> potentialCollisions;
    for (int i = 0; i < mCells.size(); i++) {
        for (size_t j = 0; j < mCells[i].objects.size(); j++) {
            for (size_t k = j + 1; k < mCells[i].objects.size(); k++) {
                potentialCollisions.emplace_back(mCells[i].objects[j], mCells[i].objects[k]);
            }
        }
    }
    return potentialCollisions;
};