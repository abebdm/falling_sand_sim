#include "particles.h"
#include "world.h"

void updateStatic(World& world, int x, int y);
void updateSand(World& world, int x, int y);
//void updateWater(int x, int y, World& world);

const ParticleProperties PARTICLE_PROPERTIES[] = {
    {"Empty", 0x000000, 0, updateStatic, UpdateDir::STATIC},
    {"Sand", 0xFAC88D, 1, updateSand, UpdateDir::FALLING},
    {"Rock", 0x888888, 5, updateStatic, UpdateDir::STATIC},
};