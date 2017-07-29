#ifndef SDLRENDERER_H_LA7HA5NV
#define SDLRENDERER_H_LA7HA5NV

#include <functional>
#include <memory>
#include <vector>

#include "irenderer.h"
#include "itexture.h"
#include "log.hpp"
#include "sdlhelpers.h"

#include <SDL2/SDL_render.h>

namespace mars {
namespace widgets {
struct Widget;
} // namespace widgets
namespace windowing {

struct SDLTexture : public ITexture {
    SDLTexture(SDL_Renderer* renderer, std::uint16_t width, std::uint16_t height, PixelFormat format);

    TextureSize size() const noexcept override;
    void put(const void* buffer, const TextureSize& size) noexcept override;
    void render(std::uint32_t x, std::uint32_t y) noexcept override;
    void UpdateYUVTexture(const Rect&, std::uint8_t*, int, std::uint8_t*, int, std::uint8_t*, int) noexcept override;

private:
    SDL_Renderer* const _renderer;
    const sdl_helpers::TexturePtr _texture;
};

struct SDLRenderer : public IRenderer {
    using LoopFn = std::function<void()>;
    SDLRenderer(SDL_Window* window);

    std::unique_ptr<ITexture> createTexture(
        std::uint16_t width, std::uint16_t height, PixelFormat format) noexcept override;

    void clear() noexcept override;
    void render() noexcept override;

    void loop(const std::vector<LoopFn>& additionalFunctions = std::vector<LoopFn>{}) noexcept;
    void addWidget(const std::shared_ptr<widgets::Widget>& w) override;

    void requestRefresh(widgets::Widget* widget) noexcept override;

private:
    const sdl_helpers::RendererPtr _renderer;
    std::vector<std::shared_ptr<widgets::Widget>> _widgets;
    std::shared_ptr<widgets::Widget> _focused;
};
} // namespace windowing
} // namespace mars

#endif /* end of include guard: SDLRENDERER_H_LA7HA5NV */
