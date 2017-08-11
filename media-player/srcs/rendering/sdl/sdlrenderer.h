#ifndef SDLRENDERER_H_LA7HA5NV
#define SDLRENDERER_H_LA7HA5NV

#include <functional>
#include <memory>
#include <vector>

#include "itexture.h"
#include "log.hpp"
#include "renderer.h"
#include "sdlhelpers.h"

#include <SDL2/SDL_render.h>

namespace mars {
namespace widgets {
struct Widget;
} // namespace widgets
namespace windowing {

struct SDLRenderer : public Renderer {
    SDLRenderer(SDL_Window* window);

    std::unique_ptr<ITexture> createTexture(
        std::uint16_t width, std::uint16_t height, PixelFormat format) noexcept override;
    std::unique_ptr<ITexture> createImage(const std::string& imagePath, bool fullscreen) override;
    std::unique_ptr<ITexture> createText(
        const std::string& text, const std::string& family, std::uint16_t size) noexcept override;

    void clear() noexcept override;
    void render() noexcept override;
    void quit() noexcept;

    void requestRefresh(widgets::Widget* widget) noexcept override;
    boost::optional<EventVariant> pollEvent() noexcept override;

    static void initialize();

    static sdl_helpers::WindowPtr createFullScreenWindow();
    static sdl_helpers::WindowPtr createSplashScreenWindow();

private:
    const sdl_helpers::RendererPtr _renderer;
    std::vector<std::shared_ptr<widgets::Widget>> _widgets;
};
} // namespace windowing
} // namespace mars

#endif /* end of include guard: SDLRENDERER_H_LA7HA5NV */
