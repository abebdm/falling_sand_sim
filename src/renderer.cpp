#include "renderer.h"
#include "world.h"
#include "particles.h"
#include <iostream>
#include <algorithm> // for std::copy

// Global static array from Particles.cpp must be declared here (or included via Particles.h)
extern const ParticleProperties PARTICLE_PROPERTIES[];

// --- Initialization and Cleanup ---

Renderer::Renderer(int width, int height) 
    : m_window_width(width * CELL_SIZE), 
      m_window_height(height * CELL_SIZE),
      m_pixel_buffer(width * height)
{
    // 1. Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL Error: " << SDL_GetError() << std::endl;
        m_isRunning = false;
        return;
    }

    // 2. Create window
    m_window = SDL_CreateWindow(
        "Falling Sand Sim (C++ Hybrid)",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        m_window_width,
        m_window_height,
        SDL_WINDOW_SHOWN
    );
    if (!m_window) {
        std::cerr << "Window could not be created! SDL Error: " << SDL_GetError() << std::endl;
        m_isRunning = false;
        return;
    }

    // 3. Create renderer
    // SDL_RENDERER_ACCELERATED uses hardware rendering (GPU) for maximum speed
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!m_renderer) {
        std::cerr << "Renderer could not be created! SDL Error: " << SDL_GetError() << std::endl;
        m_isRunning = false;
        return;
    }
    
    // 4. Create the main texture
    // We use SDL_PIXELFORMAT_ARGB8888 for easy CPU manipulation (32-bit)
    m_texture = SDL_CreateTexture(
        m_renderer, 
        SDL_PIXELFORMAT_ARGB8888, 
        SDL_TEXTUREACCESS_STREAMING, // STREAMING allows us to update the texture every frame
        width, 
        height
    );
    if (!m_texture) {
        std::cerr << "Texture could not be created! SDL Error: " << SDL_GetError() << std::endl;
        m_isRunning = false;
        return;
    }

    std::cout << "Renderer initialized successfully: " << width << "x" << height << " cells, " 
              << m_window_width << "x" << m_window_height << " pixels." << std::endl;
}

Renderer::~Renderer() {
    if (m_texture) SDL_DestroyTexture(m_texture);
    if (m_renderer) SDL_DestroyRenderer(m_renderer);
    if (m_window) SDL_DestroyWindow(m_window);
    SDL_Quit();
}

// --- Helper Function ---

// Converts the 24-bit RGB integer (0xRRGGBB) to a 32-bit ARGB format expected by the texture.
uint32_t Renderer::RGBToUint32(uint32_t rgb) const {
    // Assuming SDL is running in an environment where the pixel format is ARGB8888 (A: 0xFF)
    // RGB is 0xRRGGBB. We add 0xFF (full opacity) as the alpha channel (0xAARRGGBB).
    return 0xFF000000 | rgb;
}

// --- Rendering Loop Implementation ---

void Renderer::Render(const World& world) {
    if (!m_isRunning || !m_renderer) return;

    const int width = world.getWidth();
    const int height = world.getHeight();
    
    // 1. Map World Data to Pixel Buffer (CPU-side)
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            const Cell& cell = world.getCell(x, y);
            const ParticleType type = cell.type;
            
            // Look up the color property for the particle type
            uint32_t rgb_color = PARTICLE_PROPERTIES[(uint8_t)type].color;
            
            // Convert to the 32-bit format required by the texture
            m_pixel_buffer[y * width + x] = RGBToUint32(rgb_color);
        }
    }

    // 2. Update Texture (Transfer data from CPU buffer to GPU Texture)
    // SDL_UpdateTexture is very fast for updating the raw pixel data
    SDL_UpdateTexture(
        m_texture, 
        NULL, // NULL means update the entire texture
        m_pixel_buffer.data(), 
        width * sizeof(uint32_t) // Pitch (bytes per row)
    );

    // 3. Render Texture to Screen
    SDL_RenderClear(m_renderer); // Clear the previous frame
    SDL_RenderCopy(m_renderer, m_texture, NULL, NULL); // Copy texture to the full renderer
    SDL_RenderPresent(m_renderer); // Swap buffers to display the new frame
}

void Renderer::HandleEvents(World& world) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            m_isRunning = false;
        }
        // Add more event handling here (keyboard, mouse clicks for placing particles, etc.)

        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_s:
                    m_selected_particle = ParticleType::SAND;
                    break;
                case SDLK_e:
                   m_selected_particle = ParticleType::EMPTY;
                   break;
                case SDLK_r:
                   m_selected_particle = ParticleType::ROCK;
                   break;
                default:
                    break;
            }
        }
    }
    int mouseX_pixels, mouseY_pixels;
    uint32_t mouseState = SDL_GetMouseState(&mouseX_pixels, &mouseY_pixels);
    if (mouseState & SDL_BUTTON(SDL_BUTTON_LEFT)) {
        int cellX = mouseX_pixels / CELL_SIZE;
        int cellY = mouseY_pixels / CELL_SIZE;
        world.setCell(cellX, cellY, m_selected_particle);
    }
}
