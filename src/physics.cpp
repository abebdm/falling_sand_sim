#include "particles.h"
#include "world.h"
#include <cstdlib>

void updateStatic(World& world, int x, int y) {
    // Static particles do not move
}

void updateSand(World& world, int x, int y) {
    if (world.isInBounds(x, y+1) && PARTICLE_PROPERTIES[(uint8_t)world.getCellNext(x, y+1).type].density < PARTICLE_PROPERTIES[(uint8_t)ParticleType::SAND].density) {
        world.setCellNext(x, y+1, ParticleType::SAND);
        world.setCellNext(x, y, ParticleType::EMPTY);
        return;
    }

    int dx = std::rand() % 2 == 0 ? -1 : 1;
    
    if (world.isInBounds(x + dx, y + 1)
    && PARTICLE_PROPERTIES[(uint8_t)world.getCellNext(x + dx, y+1).type].density < PARTICLE_PROPERTIES[(uint8_t)ParticleType::SAND].density
    && PARTICLE_PROPERTIES[(uint8_t)world.getCellNext(x + dx, y).type].density < PARTICLE_PROPERTIES[(uint8_t)ParticleType::SAND].density) {
        world.setCellNext(x + dx, y + 1, ParticleType::SAND);
        world.setCellNext(x, y, ParticleType::EMPTY);
        return;
    }

    if (world.isInBounds(x - dx, y + 1)
    && PARTICLE_PROPERTIES[(uint8_t)world.getCellNext(x - dx, y+1).type].density < PARTICLE_PROPERTIES[(uint8_t)ParticleType::SAND].density
    && PARTICLE_PROPERTIES[(uint8_t)world.getCellNext(x - dx, y).type].density < PARTICLE_PROPERTIES[(uint8_t)ParticleType::SAND].density) {
        world.setCellNext(x - dx, y + 1, ParticleType::SAND);
        world.setCellNext(x, y, ParticleType::EMPTY);
        return;
    }
}