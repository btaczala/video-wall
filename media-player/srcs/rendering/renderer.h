#ifndef IRENDERER_H_HBWR9AKY
#define IRENDERER_H_HBWR9AKY

#include <cstdint>
#include <functional>
#include <memory>
#include <utility>
#include <vector>

#include <boost/optional.hpp>

#include "renderer_types.hpp"

namespace mars {
namespace widgets {
struct Widget;
} // namespace widgets
namespace windowing {

struct ITexture;
struct IFont;
struct IImage;

/**
 * @brief This is a base class for windowing system
 *  Provides a surface with a buffer where all other widgets are rendering.
 *  Each widget (texture) has to be associated with a renderer to know where to actually render.
 */
struct Renderer {
    using LoopFn = std::function<void()>;
    virtual ~Renderer() = default;

    /**
     * @brief Creates a texture
     * @return a unique pointer to newly created format
     */
    virtual std::unique_ptr<ITexture> createTexture(std::uint16_t width, std::uint16_t height, PixelFormat e) noexcept
        = 0;
    virtual std::unique_ptr<ITexture> createText(
        const std::string& text, const std::string& family, std::uint16_t size) noexcept
        = 0;

    virtual std::unique_ptr<IImage> createImage(const std::string& imagePath, bool fullscreen) noexcept = 0;

    /**
     * @brief Clears a renderer
     *  This function is used to prepare before actuall rendering
     */
    virtual void clear() noexcept = 0;

    /**
     * @brief This function copies renderer buffor to actuall window buffer
     */
    virtual void render() noexcept = 0;

    virtual void requestRefresh(widgets::Widget* = nullptr) noexcept = 0;

    virtual boost::optional<EventVariant> pollEvent() noexcept = 0;

    void addWidget(const std::shared_ptr<widgets::Widget>& w);
    void loop(const std::vector<LoopFn>& additionalFunctions = std::vector<LoopFn>{}) noexcept;

private:
    std::vector<std::shared_ptr<widgets::Widget>> _widgets;
    std::shared_ptr<widgets::Widget> _focused;
};
} // namespace windowing
} // namespace mars

#endif /* end of include guard: IRENDERER_H_HBWR9AKY */
