#ifndef SDLRENDERER_H_LA7HA5NV
#define SDLRENDERER_H_LA7HA5NV

#include "log.hpp"
#include "irenderer.h"
#include "sdlhelpers.hpp"

#include <SDL2/SDL_render.h>

namespace mars {
namespace ui {

struct SDLTexture : public ITexture {
    SDLTexture(SDL_Renderer* renderer, std::uint16_t width,
               std::uint16_t height);

    TextureSize size() const noexcept override;
    void put(const void* buffer, const TextureSize& size) noexcept override;
    void render() noexcept override;

   private:
    SDL_Renderer* const  _renderer;
    const sdl_helpers::TexturePtr _texture;
};

struct SDLRenderer : public IRenderer {
    SDLRenderer(SDL_Window* window);

    virtual std::unique_ptr<ITexture> createTexture(
        std::uint16_t width, std::uint16_t height) noexcept;

    virtual void clear() noexcept;
    virtual void render() noexcept;

   private:
    const sdl_helpers::RendererPtr _renderer;
};
}
}

#endif /* end of include guard: SDLRENDERER_H_LA7HA5NV */
