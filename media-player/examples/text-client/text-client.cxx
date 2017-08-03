#include "iconfigurationmanager.h"
#include "log.hpp"
#include "sdlrenderer.h"
#include "text/textwidget.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

struct DummyConfigurationManager : public mars::core::IConfigurationManager {
    std::string uuid() const override { return ""; }
    std::vector<std::string> fontsPaths() const override { return { { "/usr/share/fonts" } }; }
};

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

        DummyConfigurationManager cfgMgr;
        renderer.addWidget(std::make_shared<mars::widgets::TextWidget>(
            "this is a simple text", "/usr/share/fonts/TTF/Hack-Regular.ttf", 24, renderer, cfgMgr));

        renderer.loop();
    }
    return 0;
}
