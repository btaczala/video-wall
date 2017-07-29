#ifndef IRENDERER_H_HBWR9AKY
#define IRENDERER_H_HBWR9AKY

#include <cstdint>
#include <memory>
#include <utility>

#include "renderer_types.hpp"

namespace mars {
namespace widgets {
struct Widget;
} // namespace widgets
namespace windowing {

struct ITexture;

/**
 * @brief This is a base class for windowing system
 *  Provides a surface with a buffer where all other widgets are rendering.
 *  Each widget (texture) has to be associated with a renderer to know where to actually render.
 */
struct IRenderer {
    virtual ~IRenderer() = default;

    /**
     * @brief Creates a texture
     * @return a unique pointer to newly created format
     */
    virtual std::unique_ptr<ITexture> createTexture(std::uint16_t width, std::uint16_t height, PixelFormat e) noexcept
        = 0;

    /**
     * @brief Clears a renderer
     *  This function is used to prepare before actuall rendering
     */
    virtual void clear() noexcept = 0;

    /**
     * @brief This function copies renderer buffor to actuall window buffer
     */
    virtual void render() noexcept = 0;

    virtual void addWidget(const std::shared_ptr<widgets::Widget>& w) = 0;

    virtual void requestRefresh() noexcept = 0;

};
} // namespace windowing
} // namespace mars

#endif /* end of include guard: IRENDERER_H_HBWR9AKY */
