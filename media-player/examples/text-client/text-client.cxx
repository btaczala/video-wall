#include "log.hpp"
#include "sdlrenderer.h"
#include "text/textwidget.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

int main()
{
    mars::windowing::SDLRenderer::initialize();

    int width = 800;
    int height = 600;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    auto window = SDL_CreateWindow("Render CEF with SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width,
        height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
    mars_debug("SDL window = {}", static_cast<void*>(window));
    if (window) {
        mars::windowing::SDLRenderer renderer{ window };

        renderer.addWidget(std::make_shared<mars::widgets::TextWidget>(
            renderer, "this is a simple text", "/usr/share/fonts/TTF/arial.ttf", 24));

        renderer.loop();
    }
    return 0;
}
