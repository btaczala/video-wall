#include "sdlrenderer.h"
#include "fps.hpp"
#include "log.hpp"
#include "renderer_types.hpp"
#include "sdlfont.h"
#include "sdltexture.h"

#include "widgets/widget.h"

namespace {
const std::uint32_t kRefreshEvent = SDL_RegisterEvents(1);
}

namespace mars {
namespace windowing {

SDLRenderer::SDLRenderer(SDL_Window* window)
    : _renderer(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED))
{
}

std::unique_ptr<ITexture> SDLRenderer::createTexture(
    std::uint16_t width, std::uint16_t height, PixelFormat format) noexcept
{
    return std::make_unique<SDLTexture>(_renderer.get(), width, height, format);
}

std::unique_ptr<IFont> SDLRenderer::createFont(const std::string& family, std::uint16_t size) noexcept
{
    return std::make_unique<SDLFont>(_renderer.get(), family, size);
}

void SDLRenderer::clear() noexcept { SDL_RenderClear(_renderer.get()); }
void SDLRenderer::render() noexcept { SDL_RenderPresent(_renderer.get()); }

void SDLRenderer::loop(const std::vector<LoopFn>& additionalFunctions) noexcept
{
    mars_info_(rendering, "Start rendering loop");
    SDL_Event ev{};
    while (true) {
        auto r = SDL_WaitEventTimeout(&ev, 10);
        if (r > 0) {
            mars_debug_(rendering, "Received event 0x{:x}", ev.type);
            if (ev.type == SDL_QUIT) {
                break;
            } else if (ev.type == SDL_KEYDOWN) {
                if (ev.key.keysym.sym == SDLK_SPACE) {
                }
            }
        }
        for (const auto& f : additionalFunctions) {
            f();
        }
        clear();
        for (const auto& w : _widgets) {
            if (w->update()) {
                w->render();
            }
        }
        render();
    }
    mars_info_(rendering, "Finish rendering loop");
}

void SDLRenderer::addWidget(const std::shared_ptr<widgets::Widget>& w)
{
    if (_widgets.empty()) {
        _focused = w;
    }
    _widgets.push_back(w);
}

void SDLRenderer::requestRefresh(widgets::Widget* widget) noexcept
{
    mars_trace_(rendering, "Scheduling a refresh");
    SDL_Event ev;
    std::memset(&ev, 0, sizeof(SDL_Event));
    ev.type = kRefreshEvent;
    ev.user.data1 = widget;
    ev.user.data2 = nullptr;

    SDL_PushEvent(&ev);
}

} // namespace windowing
} // namespace mars
