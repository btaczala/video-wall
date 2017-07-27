
#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Window.hh>

#include <thread>

#include "ffmpegrenderer.h"
#include "sdlrenderer.h"
#include "widgets/videowidget.h"

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

        mars::ui::SDLRenderer sdlRenderer{ window.Get() };
        mars::rendering::FFMPEGBackend videoBackend;
        const std::string url = argv[1];
        mars::ui::widgets::VideoWidget vw{ url, sdlRenderer, videoBackend };

        SDL_Event ev;
        bool started = false;

        while (true) {
            auto r = SDL_WaitEventTimeout(&ev, 40);
            if (r > 0) {
                mars_trace("Received event 0x{:x}", ev.type);
                if (ev.type == SDL_QUIT) {
                    break;
                } else if (ev.type == SDL_KEYDOWN) {
                    if (ev.key.keysym.sym == SDLK_SPACE) {
                        mars_debug("Staring playback");
                        started = !started;
                    }
                }
            }
            sdlRenderer.clear();
            if (started) {
                if (vw.update()) {
                    vw.render();
                }
            }

            sdlRenderer.render();
        }

    } catch (const std::exception& ex) {
    }
}
