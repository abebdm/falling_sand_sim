#include "world.h"

int World::getWidth() const {
    return width;
}

int World::getHeight() const {
    return height;
}

bool World::isInBounds(int x, int y) const {
    return x >= 0 && x < width && y >= 0 && y < height;
}

const Cell& World::getCell(int x, int y) const {
    return current_state[y * width + x];
}

const Cell& World::getCellNext(int x, int y) const {
    return next_state[y * width + x];
}

void World::setCell(int x, int y, ParticleType type) {
    if (isInBounds(x, y)) current_state[y * width + x].type = type;
}

void World::setCellNext(int x, int y, ParticleType type) {
    if (isInBounds(x, y)) next_state[y * width + x].type = type;
}

void World::simulateStep() {
    next_state = current_state;

    for(int y = height - 1; y >= 0; --y) {
        for(int x = 0; x < width; ++x) {
            
            ParticleType type = getCell(x, y).type; // Read from current_state
            if (type == ParticleType::EMPTY) continue;
            
            const auto& props = PARTICLE_PROPERTIES[(int)type];
            if (props.updateDir == UpdateDir::FALLING) {
                props.updateFunction(*this, x, y); // Writes to next_state
            }
        }
    }

    for(int y = 0; y < height; ++y) {
        for(int x = 0; x < width; ++x) {

            ParticleType type = getCell(x, y).type; // Read from current_state
            if (type == ParticleType::EMPTY) continue;
            
            const auto& props = PARTICLE_PROPERTIES[(int)type];
            if (props.updateDir == UpdateDir::RISING) {
                props.updateFunction(*this, x, y); // Writes to next_state
            }
        }
    }

    current_state = next_state;
}

World::World(int width, int height)
    : width(width), height(height),
      current_state(width * height, {ParticleType::EMPTY, 0}),
      next_state(width * height, {ParticleType::EMPTY, 0}) {}