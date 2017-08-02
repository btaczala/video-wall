
#include <SDL2/SDL.h>
#include <iostream>

#include "sdlrenderer.h"
#include "video/ffmpegrenderer.h"
#include "video/videowidget.h"

int main(int argc, char* argv[])
{
    if (argc < 2) {
        return EXIT_FAILURE;
    }
    mars::windowing::SDLRenderer::initialize();
    auto window = mars::windowing::SDLRenderer::createFullScreenWindow();

    mars::windowing::SDLRenderer sdlRenderer{ window.get() };
    mars::rendering::FFMPEGBackend videoBackend;
    const std::string url = argv[1];

    auto video = std::make_shared<mars::widgets::VideoWidget>(url, sdlRenderer, videoBackend);
    sdlRenderer.addWidget(video);

    video->move(100, 100);

    // this will block
    sdlRenderer.loop();
}
