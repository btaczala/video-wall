#ifndef SDLRENDERER_H_LA7HA5NV
#define SDLRENDERER_H_LA7HA5NV

#include <memory>
#include <vector>

#include "irenderer.h"
#include "itexture.h"
#include "log.hpp"
#include "sdlhelpers.hpp"

#include <SDL2/SDL_render.h>

namespace mars {
namespace widgets {
struct IWidget;
}
namespace windowing {

struct SDLTexture : public ITexture {
    SDLTexture(SDL_Renderer* renderer, std::uint16_t width, std::uint16_t height, PixelFormat format);

    TextureSize size() const noexcept override;
    void put(const void* buffer, const TextureSize& size) noexcept override;
    void render() noexcept override;
    void UpdateYUVTexture(const Rect&, std::uint8_t*, int, std::uint8_t*, int, std::uint8_t*, int) noexcept override;

private:
    SDL_Renderer* const _renderer;
    const sdl_helpers::TexturePtr _texture;
};

struct SDLRenderer : public IRenderer {
    SDLRenderer(SDL_Window* window);

    virtual std::unique_ptr<ITexture> createTexture(
        std::uint16_t width, std::uint16_t height, PixelFormat format) noexcept override;

    virtual void clear() noexcept override;
    virtual void render() noexcept override;

    void loop() noexcept;

    virtual void addWidget(const std::shared_ptr<widgets::IWidget>& w) override;

private:
    const sdl_helpers::RendererPtr _renderer;
    std::vector<std::shared_ptr<widgets::IWidget>> _widgets;
    std::shared_ptr<widgets::IWidget> _focused;
};
}
}

#endif /* end of include guard: SDLRENDERER_H_LA7HA5NV */
