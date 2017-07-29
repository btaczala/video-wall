#include "sdlrenderer.h"
#include "widgets/widget.h"

#include "log.hpp"

namespace {

int convertPixelFormat(mars::windowing::PixelFormat format)
{
    if (format == mars::windowing::PixelFormat::Unknown) {
        return SDL_PIXELFORMAT_UNKNOWN;
    } else if (format == mars::windowing::PixelFormat::IYUV) {
        return SDL_PIXELFORMAT_IYUV;
    }

    return SDL_PIXELFORMAT_UNKNOWN;
}
} // namespace

namespace mars {
namespace windowing {

SDLTexture::SDLTexture(SDL_Renderer* renderer, std::uint16_t width, std::uint16_t height, PixelFormat format)
    : _renderer(renderer)
    , _texture(SDL_CreateTexture(_renderer, ::convertPixelFormat(format), SDL_TEXTUREACCESS_STREAMING, width, height))
{
}

ITexture::TextureSize SDLTexture::size() const noexcept
{
    int w, h;
    SDL_QueryTexture(_texture.get(), nullptr, nullptr, &w, &h);
    return std::make_pair(w, h);
}

void SDLTexture::put(const void* buffer, const TextureSize& size) noexcept
{
    const auto tSize = this->size();
    if (tSize != size) {
        return;
    }

    unsigned char* texture_data = nullptr;
    int texture_pitch = 0;
    SDL_LockTexture(_texture.get(), nullptr, reinterpret_cast<void**>(&texture_data), &texture_pitch);
    memcpy(texture_data, buffer, size.first * size.second * 4);
    SDL_UnlockTexture(_texture.get());
}

void SDLTexture::render() noexcept
{
    auto si = size();
    SDL_Rect r{};
    r.x = 0;
    r.y = 0;
    r.w = si.first;
    r.h = si.second;
    SDL_RenderCopy(_renderer, _texture.get(), nullptr, &r);
}
void SDLTexture::UpdateYUVTexture(const Rect& rect, std::uint8_t* yplane, int ypitch, std::uint8_t* uplane, int upitch,
    std::uint8_t* vplane, int vpitch) noexcept
{
    SDL_Rect sdl_rect{};
    sdl_rect.x = rect.x;
    sdl_rect.y = rect.y;
    sdl_rect.w = rect.w;
    sdl_rect.h = rect.h;
    SDL_UpdateYUVTexture(_texture.get(), &sdl_rect, yplane, ypitch, uplane, upitch, vplane, vpitch);
}

SDLRenderer::SDLRenderer(SDL_Window* window)
    : _renderer(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED))
{
}

std::unique_ptr<ITexture> SDLRenderer::createTexture(
    std::uint16_t width, std::uint16_t height, PixelFormat format) noexcept
{
    return std::make_unique<SDLTexture>(_renderer.get(), width, height, format);
}

void SDLRenderer::clear() noexcept { SDL_RenderClear(_renderer.get()); }
void SDLRenderer::render() noexcept { SDL_RenderPresent(_renderer.get()); }

void SDLRenderer::loop(const std::vector<LoopFn>& additionalFunctions) noexcept
{
    mars_info_(rendering, "Start rendering loop");
    SDL_Event ev{};
    while (true) {
        // TODO: For now this is super wrong for rendering ffmpeg frames, as this 
        // will render movie in a fast forward mode. 
        // Either we can buffer 
        auto r = SDL_PollEvent(&ev);
        if (r > 0) {
            mars_trace_(rendering, "Received event 0x{:x}", ev.type);
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

} // namespace windowing
} // namespace mars
