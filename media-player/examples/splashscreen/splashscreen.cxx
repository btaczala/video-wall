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
    auto marsLogo = std::make_shared<ImageWidget>(std::string{ TEST_DIR } + "/mars.png", ImageType::normal, renderer);

    marsLogo->setRect(Rect{ 100, 150, 100, 40 });

    auto textWidget = std::make_shared<TextWidget>("Welcome to MARS", fontPath, 28, renderer, cfgMgr);

    textWidget->move(230, 150);

    renderer.addWidget(imageWidget);
    renderer.addWidget(textWidget);
    renderer.addWidget(marsLogo);
    renderer.setFocus(textWidget);

    // textWidget->addBackground();

    std::thread quitThread{ [&]() {
        std::unique_lock<std::mutex> lk(mtx);
        cv.wait_for(lk, std::chrono::seconds(timeout));
        renderer.quit();
    } };

    std::thread animationThread{ [&]() {
        int offset = 5;
        while (true) {
            std::unique_lock<std::mutex> lk(mtx);
            auto st = cv.wait_for(lk, std::chrono::milliseconds(15));
            if (st != std::cv_status::timeout) {
                break;
            } else {
                // offset += 1;
                textWidget->move(textWidget->x() - offset, textWidget->y());
                marsLogo->move(marsLogo->x() - offset, marsLogo->y());

                if (textWidget->x() < -250) {
                    // offset = 0;
                    textWidget->move(renderer.geometry().w, 150);
                    marsLogo->move(renderer.geometry().w - 130, 150);
                }
            }
        }
    } };

    renderer.loop();
    cv.notify_all();

    quitThread.join();
    animationThread.join();

    return 0;
}
