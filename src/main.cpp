#include "world.h"
#include "particles.h"
#include "renderer.h"
#include <SDL.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

const int WORLD_WIDTH = 250;
const int WORLD_HEIGHT = 250;

int main(int argc, char* argv[]) {
    std::srand(std::time(0));

    World world(WORLD_WIDTH, WORLD_HEIGHT);
    Renderer renderer(WORLD_WIDTH, WORLD_HEIGHT);

    while (renderer.IsRunning()) {
        renderer.HandleEvents(world);
        // world.setCell(WORLD_WIDTH / 2, 0, ParticleType::SAND); // Spawn sand at the top center
        world.simulateStep();
        renderer.Render(world);
    }
    return 0;
}