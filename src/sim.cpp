#include <cstdint>
#include <vector>
#include <string>

using UpdateFn = void (*)(int x, int y);

enum class ParticleType : uint8_t{
    EMPTY = 0,
    
    SAND = 1,

    //WATER = 10,

    TYPE_COUNT
};

struct Cell {
    ParticleType type;
    uint8_t state; // Additional state information for the cell
};

struct ParticleProperties {
    std::string name;
    uint32_t color;
    int8_t density;
    UpdateFn updateFunction;
};

const ParticleProperties particleProperties[] = {
    {"Empty", 0x00000000, 0, nullptr},
    {"Sand", 0xFFC2B280, 2, nullptr},
    //{"Water", 0xFF0000FF, 1, nullptr},
};

