#pragma once

#include "particles.h"
#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <cstdint>

class World;

class Renderer {
public:
    // Renderer parameters (should be defined based on your World dimensions)
    static constexpr int CELL_SIZE = 4; // 1 pixel per particle
    
    // Constructor initializes SDL, creates window and renderer
    Renderer(int width, int height);

    // Destructor cleans up all SDL resources
    ~Renderer();

    // Main drawing function: reads World data and updates the screen
    void Render(const World& world);

    // Check if the window is closed
    bool IsRunning() const { return m_isRunning; }

    // Handle input events (like closing the window)
    void HandleEvents(World&);

    // Helper to map 24-bit RGB (used in ParticleProperties) to 32-bit format (used by SDL texture)
    uint32_t RGBToUint32(uint32_t rgb) const;

private:
    SDL_Window* m_window = nullptr;
    SDL_Renderer* m_renderer = nullptr;
    SDL_Texture* m_texture = nullptr; // The main texture holding the particle pixels
    
    int m_window_width;
    int m_window_height;
    bool m_isRunning = true;

    // A pixel buffer in CPU memory that is locked and copied to the GPU texture
    std::vector<uint32_t> m_pixel_buffer;

    ParticleType m_selected_particle = ParticleType::SAND;
};