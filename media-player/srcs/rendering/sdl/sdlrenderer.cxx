#include "sdlrenderer.h"
#include "fps.hpp"
#include "log.hpp"
#include "renderer_types.hpp"
#include "sdlfont.h"
#include "sdltexture.h"

#include "widgets/widget.h"

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <spdlog/fmt/fmt.h>

namespace {
const std::uint32_t kRefreshEvent = SDL_RegisterEvents(1);
} // namespace

namespace mars {
namespace windowing {

SDLRenderer::SDLRenderer(SDL_Window* window)
    : _renderer(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED))
{
    int w, h;
    SDL_GetRendererOutputSize(_renderer.get(), &w, &h);
    mars_info_(rendering, "Created a renderer {} size {}x{}", static_cast<void*>(_renderer.get()), w, h);
}

std::unique_ptr<ITexture> SDLRenderer::createTexture(
    std::uint16_t width, std::uint16_t height, PixelFormat format) noexcept
{
    return std::make_unique<SDLTexture>(_renderer.get(), width, height, format);
}

std::unique_ptr<ITexture> SDLRenderer::createText(
    const std::string& text, const std::string& family, std::uint16_t size) noexcept
{
    mars_info_(rendering, "createText(text={}, font={}, size={})", text, family, size);
    SDLFont f{ _renderer.get(), family, size };
    return f.renderText(text);
}

std::unique_ptr<ITexture> SDLRenderer::createImage(const std::string& imagePath, bool fullscreen) noexcept
{
    auto surf = IMG_Load(imagePath.c_str());

    return std::make_unique<SDLTexture>(
        _renderer.get(), SDL_CreateTextureFromSurface(_renderer.get(), surf), fullscreen);
}

void SDLRenderer::clear() noexcept { SDL_RenderClear(_renderer.get()); }
void SDLRenderer::render() noexcept { SDL_RenderPresent(_renderer.get()); }
void SDLRenderer::quit() noexcept
{
    mars_debug_(rendering, "Quiting rendering");
    SDL_Event ev;
    std::memset(&ev, 0, sizeof(SDL_Event));
    ev.type = SDL_QUIT;
    SDL_PushEvent(&ev);
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

boost::optional<EventVariant> SDLRenderer::pollEvent() noexcept
{
    SDL_Event ev{};
    auto r = SDL_WaitEventTimeout(&ev, 10);
    if (r > 0) {
        mars_trace_(rendering, "Received event 0x{:x}", ev.type);
        return sdl_helpers::translateEvent(ev);
    }

    return boost::optional<EventVariant>{};
}

void /* static */ SDLRenderer::initialize()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        mars_error_(rendering, "Unable to init sdl ec = {}", SDL_GetError());
        throw std::runtime_error(fmt::format("Unable to init sdl ec = {}", SDL_GetError()));
    }
    if (TTF_Init() < 0) {
        mars_error_(rendering, "Unable to init ttl ec = {}", TTF_GetError());
        throw std::runtime_error(fmt::format("Unable to init ttl ec = {}", TTF_GetError()));
    }

    int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_TIF;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        mars_error_(rendering, "Unable to init image library ec = {}", IMG_GetError());
        throw std::runtime_error(fmt::format("Unable to init image library ec = {}", IMG_GetError()));
    }

    SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
    SDL_EventState(SDL_KEYDOWN, SDL_IGNORE);
}

/*static*/ sdl_helpers::WindowPtr SDLRenderer::createFullScreenWindow()
{
    const int width = 800;
    const int height = 600;
    auto window = SDL_CreateWindow("Render CEF with SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width,
        height, SDL_WINDOW_FULLSCREEN_DESKTOP | SDL_WINDOW_OPENGL);

    if (!window) {
        mars_error_(rendering, "Unable to create window SDL_GetError()={}", SDL_GetError());
        throw std::runtime_error("Unable to create window");
    }
    return sdl_helpers::WindowPtr{ window };
}

/*static*/ sdl_helpers::WindowPtr SDLRenderer::createSplashScreenWindow()
{
    const int width = 700;
    const int height = 500;
    auto window = SDL_CreateWindow(
        "Splash window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_OPENGL);

    if (!window) {
        mars_error_(rendering, "Unable to create window SDL_GetError()={}", SDL_GetError());
        throw std::runtime_error("Unable to create window");
    }

    return sdl_helpers::WindowPtr{ window };
}

} // namespace windowing
} // namespace mars
