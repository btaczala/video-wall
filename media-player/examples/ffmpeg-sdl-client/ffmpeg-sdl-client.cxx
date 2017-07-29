
#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Window.hh>

#include <thread>

#include "sdlrenderer.h"
#include "video/ffmpegrenderer.h"
#include "video/videowidget.h"

int main(int argc, char* argv[])
{
    if (argc < 2) {
        return EXIT_FAILURE;
    }
    using namespace SDL2pp;
    try {
        SDL sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

        Window window("libSDL2pp demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_OPENGL);
        window.SetFullscreen(SDL_WINDOW_FULLSCREEN_DESKTOP);

        mars::windowing::SDLRenderer sdlRenderer{ window.Get() };
        mars::rendering::FFMPEGBackend videoBackend;
        const std::string url = argv[1];

        sdlRenderer.addWidget(std::make_shared<mars::widgets::VideoWidget>(url, sdlRenderer, videoBackend));

        // this will block
        sdlRenderer.loop();

    } catch (const std::exception& ex) {
    }
}
