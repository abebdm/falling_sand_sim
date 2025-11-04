#include "particles.h"
#include "world.h"
#include <cstdlib>

void updateStatic(World& world, int x, int y) {
    // Static particles do not move
}

void updateSand(World& world, int x, int y) {
    if (world.isInBounds(x, y+1) && world.getCellNext(x, y+1).type == ParticleType::EMPTY) {
        world.setCellNext(x, y+1, ParticleType::SAND);
        world.setCellNext(x, y, ParticleType::EMPTY);
        return;
    }

    int dx = std::rand() % 2 == 0 ? -1 : 1;
    if (world.isInBounds(x + dx, y + 1) && world.getCellNext(x + dx, y + 1).type == ParticleType::EMPTY) {
        world.setCellNext(x + dx, y + 1, ParticleType::SAND);
        world.setCellNext(x, y, ParticleType::EMPTY);
        return;
    }

    if (world.isInBounds(x - dx, y + 1) && world.getCellNext(x - dx, y + 1).type == ParticleType::EMPTY) {
        world.setCellNext(x - dx, y + 1, ParticleType::SAND);
        world.setCellNext(x, y, ParticleType::EMPTY);
        return;
    }
}