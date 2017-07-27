#include "sdlrenderer.h"

namespace {

int convertPixelFormat(mars::ui::PixelFormat format)
{
    if (format == mars::ui::PixelFormat::Unknown) {
        return SDL_PIXELFORMAT_UNKNOWN;
    } else if (format == mars::ui::PixelFormat::IYUV) {
        return SDL_PIXELFORMAT_IYUV;
    }

    return SDL_PIXELFORMAT_UNKNOWN;
}
}

namespace mars {
namespace ui {

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
    if (tSize != size)
        return;

    unsigned char* texture_data = NULL;
    int texture_pitch = 0;
    SDL_LockTexture(_texture.get(), 0, reinterpret_cast<void**>(&texture_data), &texture_pitch);
    memcpy(texture_data, buffer, size.first * size.second * 4);
    SDL_UnlockTexture(_texture.get());
}

void SDLTexture::render() noexcept
{
    auto si = size();
    SDL_Rect r;
    r.x = 0;
    r.y = 0;
    r.w = si.first;
    r.h = si.second;
    SDL_RenderCopy(_renderer, _texture.get(), nullptr, &r);
}
void SDLTexture::UpdateYUVTexture(const Rect& rect, std::uint8_t* yplane, int ypitch, std::uint8_t* uplane, int upitch,
    std::uint8_t* vplane, int vpitch) noexcept
{
    SDL_Rect sdl_rect;
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

std::unique_ptr<ITexture> SDLRenderer::createTexture(std::uint16_t w, std::uint16_t h, PixelFormat format) noexcept
{
    return std::make_unique<SDLTexture>(_renderer.get(), w, h, format);
}

void SDLRenderer::clear() noexcept { SDL_RenderClear(_renderer.get()); }
void SDLRenderer::render() noexcept { SDL_RenderPresent(_renderer.get()); }
}
}
