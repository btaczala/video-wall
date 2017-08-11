#include "iconfigurationmanager.h"
#include "image/imagewidget.h"
#include "log.hpp"
#include "sdlrenderer.h"
#include "text/textwidget.h"

#include <condition_variable>
#include <iostream>
#include <thread>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <boost/filesystem.hpp>

struct DummyConfigurationManager : public mars::core::IConfigurationManager {
    std::string uuid() const override { return ""; }
    std::vector<std::string> fontsPaths() const override { return { { boost::filesystem::current_path().string() } }; }
};

int main()
{
    using namespace mars::windowing;
    using namespace mars::widgets;
    SDLRenderer::initialize();

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

    auto window = SDLRenderer::createSplashScreenWindow();

    auto timeout = 5;
    std::mutex mtx;
    std::condition_variable cv;

    SDLRenderer renderer{ window.get() };
    DummyConfigurationManager cfgMgr;

    const std::string imagePath = std::string{ TEST_DIR } + "/mars.jpg";
    const std::string fontPath = std::string{ TEST_DIR } + "/Hack-Regular.ttf";
    auto imageWidget = std::make_shared<ImageWidget>(imagePath, ImageType::stretched, renderer);

    auto textWidget = std::make_shared<TextWidget>("Welcome to MARS", fontPath, 28, renderer, cfgMgr);

    textWidget->move(230, 150);

    renderer.addWidget(imageWidget);
    renderer.addWidget(textWidget);
    textWidget->addBackground();

    std::thread quitThread{ [&]() {
        std::unique_lock<std::mutex> lk(mtx);
        cv.wait_for(lk, std::chrono::seconds(timeout));
        renderer.quit();
    } };

    renderer.loop();
    cv.notify_one();

    quitThread.join();

    return 0;
}
