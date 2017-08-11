#include "sdltexture.h"
#include "log.hpp"
#include "sdllogging.hpp"

#include <SDL2/SDL_render.h>
#include <boost/assert.hpp>
#include <spdlog/fmt/fmt.h>

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
    if (!_texture) {
        auto f = fmt::format("Unable to SDL_CreateTexture({}, {}, {}, {}, {}). SDL_GetError={})",
            static_cast<void*>(_renderer), static_cast<int>(format), "SDL_TEXTUREACCESS_STREAMING", width, height,
            SDL_GetError());
        mars_error_(rendering, "{}", f);
        throw std::runtime_error(f);
    }
    mars_debug_(rendering, "SDLTexture::SDLTexture _texture = {}", static_cast<void*>(_texture.get()));
}

SDLTexture::SDLTexture(SDL_Renderer* renderer, SDL_Texture* texture, bool fullscreen /* = false*/)
    : _renderer(renderer)
    , _texture(texture)
{
    setFullscreen(fullscreen);
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
    std::memcpy(texture_data, buffer, size.first * size.second * 4);
    SDL_UnlockTexture(_texture.get());
}

void SDLTexture::render(std::uint32_t x, std::uint32_t y) noexcept
{
    BOOST_ASSERT_MSG(_texture, "Texture cannot be null");
    BOOST_ASSERT_MSG(_renderer, "Renderer cannot be null");
    auto si = size();
    SDL_Rect destRect{};
    destRect.x = x;
    destRect.y = y;
    destRect.w = si.first;
    destRect.h = si.second;

    SDL_Rect srcRect{ 0, 0, si.first, si.second };
    if (!_fullscreen) {
        mars_debug_(rendering, "[{}] Rendering texture {} under rect {} {}", static_cast<void*>(this),
            static_cast<void*>(_texture.get()), srcRect, destRect);
        SDL_RenderCopy(_renderer, _texture.get(), &srcRect, &destRect);
    } else {
        mars_trace_(rendering, "[{}] Rendering texture fullscreen ", static_cast<void*>(this));
        SDL_RenderCopy(_renderer, _texture.get(), nullptr, nullptr);
    }
}
void SDLTexture::UpdateYUVTexture(const Rect& rect, std::uint8_t* yplane, int ypitch, std::uint8_t* uplane, int upitch,
    std::uint8_t* vplane, int vpitch) noexcept
{
    SDL_Rect sdl_rect{};
    sdl_rect.x = rect.x;
    sdl_rect.y = rect.y;
    sdl_rect.w = rect.w;
    sdl_rect.h = rect.h;
    mars_debug_(rendering, "[{}] Rendering YUV texture {} under rect {} ", static_cast<void*>(this),
        static_cast<void*>(_texture.get()), sdl_rect);
    SDL_UpdateYUVTexture(_texture.get(), &sdl_rect, yplane, ypitch, uplane, upitch, vplane, vpitch);
}
} // namespace windowing
} // namespace mars
