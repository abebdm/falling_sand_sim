#pragma once

#include <cstdint>
#include <string>

class World; // Forward declaration

enum class ParticleType : uint8_t{
    EMPTY = 0,
    
    SAND = 1,

    //WATER = 10,

    TYPE_COUNT
};

enum class UpdateDir {
    STATIC,
    FALLING,
    RISING
};

struct Cell {
    ParticleType type;
    uint8_t state; // Additional state information for the cell
};

using UpdateFn = void (*)(World& world, int x, int y);

struct ParticleProperties {
    std::string name;
    uint32_t color;
    int8_t density;
    UpdateFn updateFunction;
    UpdateDir updateDir;
};

extern const ParticleProperties PARTICLE_PROPERTIES[];