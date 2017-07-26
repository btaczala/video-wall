#include "sdlrenderer.h"

namespace mars {
namespace ui {

    SDLTexture::SDLTexture(SDL_Renderer* renderer, std::uint16_t width, std::uint16_t height)
        : _renderer(renderer)
        , _texture(SDL_CreateTexture(_renderer, SDL_PIXELFORMAT_UNKNOWN, SDL_TEXTUREACCESS_STREAMING, width, height))
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

    void SDLTexture::render() noexcept { SDL_RenderCopy(_renderer, _texture.get(), nullptr, nullptr); }

    SDLRenderer::SDLRenderer(SDL_Window* window)
        : _renderer(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED))
    {
    }

    std::unique_ptr<ITexture> SDLRenderer::createTexture(std::uint16_t w, std::uint16_t h) noexcept
    {
        return std::make_unique<SDLTexture>(_renderer.get(), w, h);
    }

    void SDLRenderer::clear() noexcept { SDL_RenderClear(_renderer.get()); }
    void SDLRenderer::render() noexcept { SDL_RenderPresent(_renderer.get()); }
}
}
