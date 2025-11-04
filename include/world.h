#pragma once

#include "particles.h"
#include <vector>

class World {
public:
    World(int width, int height);
    ~World() = default;

    void simulateStep();
    void setCell(int x, int y, ParticleType type);
    void setCellNext(int x, int y, ParticleType type);
    const Cell& getCell(int x, int y) const;
    const Cell& getCellNext(int x, int y) const;
    bool isInBounds(int x, int y) const;
    int getWidth() const;
    int getHeight() const;

private:
    int width;
    int height;

    std::vector<Cell> current_state;
    std::vector<Cell> next_state;
};