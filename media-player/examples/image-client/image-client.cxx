#include "image/imagewidget.h"
#include "log.hpp"
#include "sdlrenderer.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

int main(int argc, char* argv[])
{

    if (argc < 2) {
        return EXIT_FAILURE;
    }

    mars::windowing::SDLRenderer::initialize();

    int width = 1000;
    int height = 800;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    auto window = SDL_CreateWindow("Render CEF with SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width,
        height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
    mars_debug("SDL window = {}", static_cast<void*>(window));
    if (window) {
        mars::windowing::SDLRenderer renderer{ window };

        renderer.addWidget(
            std::make_shared<mars::widgets::ImageWidget>(argv[1], mars::windowing::ImageType::stretched, renderer));

        renderer.loop();
    }
    return 0;
}
