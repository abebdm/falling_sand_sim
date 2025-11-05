#include "world.h"
#include "particles.h"
#include "renderer.h"
#include <SDL.h>
#include <iostream>
#include <cstdlib>
#include <ctime>

const int WORLD_WIDTH = 250;
const int WORLD_HEIGHT = 250;
const int TARGET_FPS = 240;
const int FRAME_DELAY = 1000 / TARGET_FPS;

int main(int argc, char* argv[]) {
    std::srand(std::time(0));

    World world(WORLD_WIDTH, WORLD_HEIGHT);
    Renderer renderer(WORLD_WIDTH, WORLD_HEIGHT);

    uint32_t frameStart;
    int frameTime;

    while (renderer.IsRunning()) {
        frameStart = SDL_GetTicks();

        renderer.HandleEvents(world);
        world.simulateStep();
        renderer.Render(world);

        frameTime = SDL_GetTicks() - frameStart;
        if (FRAME_DELAY > frameTime) {
            SDL_Delay(FRAME_DELAY - frameTime);
        } else {
            std::cout << "Warning: Frame took longer than target frame time!" << std::endl;
        }
    }
    return 0;
}