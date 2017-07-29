#include <iostream>
#include <sstream>
#include <stdio.h>

#include <SDL.h>
#include <unistd.h>

#include <cef_app.h>
#include <cef_client.h>
#include <cef_life_span_handler.h>
#include <cef_load_handler.h>
#include <cef_render_handler.h>
#include <wrapper/cef_helpers.h>

#include "fps.hpp"
#include "html/cefbrowserclient.h"
#include "html/cefrenderhandler.h"
#include "log.hpp"
#include "sdlrenderer.h"
#include "stopwatch.hpp"

int main(int argc, char* argv[])
{

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

    // Initialize SDL
    mars_debug("Initializing SDL pid = {}", getpid());
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return 1;
    }

    int width = 800;
    int height = 600;

    auto window = SDL_CreateWindow("Render CEF with SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width,
        height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_OPENGL);
    mars_debug("SDL window = {}", static_cast<void*>(window));
    if (window) {
        mars::windowing::SDLRenderer renderer{ window };
        if (true) {
            // SDL_Event e;

            // CefRefPtr<mars::webengine::RenderHandler> renderHandler
            //= new mars::webengine::RenderHandler(&renderer, width * 2, height * 2);

            //// create browser-window
            // CefRefPtr<CefBrowser> browser;
            // CefRefPtr<mars::webengine::BrowserClient> browserClient;

            //{
            // CefWindowInfo window_info;
            // CefBrowserSettings browserSettings;
            // browserSettings.webgl = STATE_ENABLED;

            // window_info.SetAsWindowless(0);
            // browserClient = new mars::webengine::BrowserClient(renderHandler);

            // const std::string url{ std::string{ "file:///" } + std::string(HTML_DIR)
            //+ "/webgl-hello-world-master/webgl-demo.htm" };
            // mars_debug("Url = {}", url);
            // browser = CefBrowserHost::CreateBrowserSync(
            // window_info, browserClient.get(), url, browserSettings, nullptr);
            //}

            // bool shutdown = false;
            // while (!browserClient->closeAllowed()) {
            //// send events to browser
            // while (!shutdown && SDL_PollEvent(&e) != 0) {
            // switch (e.type) {
            // case SDL_QUIT:
            // shutdown = true;
            // browser->GetHost()->CloseBrowser(false);
            // break;
            //}
            //}

            //// let browser process events
            // CefDoMessageLoopWork();

            //// render
            // renderer.clear();

            ////renderHandler->render(40,40);

            //// Update screen
            // renderer.render();
            //}

            // browser = nullptr;
            // browserClient = nullptr;
            // renderHandler = nullptr;

            // CefShutdown();
            //}
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
