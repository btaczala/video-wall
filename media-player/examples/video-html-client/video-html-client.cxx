#include <cstdlib>
#include <iostream>

#include <SDL2/SDL.h>
#include <cef_app.h>

#include "html/htmlwidget.h"
#include "sdlrenderer.h"
#include "video/ffmpegrenderer.h"
#include "video/videowidget.h"

int main(int argc, char* argv[])
{
    if (argc < 3) {
        return EXIT_FAILURE;
    }
    mars_debug("Star rendering html content pid = {}", getpid());

    CefMainArgs args(argc, argv);

    {
        int result = CefExecuteProcess(args, nullptr, nullptr);
        if (result >= 0) {
            // child proccess has endend, so exit.
            return result;
        } else if (result == -1) {
            // we are here in the father proccess.
        }
    }

    {
        CefSettings settings;
        settings.no_sandbox = 1;
        // settings.log_severity = LOGSEVERITY_VERBOSE;

        {
            std::ostringstream ss;
            ss << SDL_GetBasePath() << "locales/";
            CefString(&settings.locales_dir_path) = ss.str();
        }

        // CefString(&settings.locales_dir_path).FromASCII("");
        CefString(&settings.resources_dir_path) = SDL_GetBasePath();

        bool result = CefInitialize(args, settings, nullptr, nullptr);
        if (!result) {
            // handle error
            return -1;
        }
    }
    {
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

        auto html = std::make_shared<mars::widgets::HTMLWidget>(argv[1], sdlRenderer, 900, 700);

        mars::rendering::FFMPEGBackend videoBackend;
        auto video = std::make_shared<mars::widgets::VideoWidget>(argv[2], sdlRenderer, videoBackend);

        sdlRenderer.addWidget(html);
        sdlRenderer.addWidget(video);

        sdlRenderer.loop({ { []() { CefDoMessageLoopWork(); } } });
    }
    CefShutdown();

    return 0;
}
