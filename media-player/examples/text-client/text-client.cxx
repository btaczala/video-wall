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
    using namespace mars::windowing;
    using namespace mars::widgets;
    SDLRenderer::initialize();

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    auto window = SDLRenderer::createFullScreenWindow();
    if (window) {
        SDLRenderer renderer{ window.get() };

        DummyConfigurationManager cfgMgr;
        renderer.addWidget(std::make_shared<TextWidget>(
            "this is a simple text", "/usr/share/fonts/TTF/Hack-Regular.ttf", 24, renderer, cfgMgr));

        renderer.loop();
    }
    return 0;
}
