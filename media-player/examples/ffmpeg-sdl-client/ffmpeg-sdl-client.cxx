
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
    int width = 800;
    int height = 600;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }
    auto window = SDL_CreateWindow("Render CEF with SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width,
        height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
    mars_debug("SDL window = {}", static_cast<void*>(window));

    mars::windowing::SDLRenderer sdlRenderer{ window };
    mars::rendering::FFMPEGBackend videoBackend;
    const std::string url = argv[1];

    auto video = std::make_shared<mars::widgets::VideoWidget>(url, sdlRenderer, videoBackend);
    sdlRenderer.addWidget(video);

    video->move(100, 100);

    // this will block
    sdlRenderer.loop();
}
