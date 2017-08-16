#ifndef WIDGET_H_G5T74RQZ
#define WIDGET_H_G5T74RQZ

#include <cstdint>

#include "renderer_types.hpp"

namespace mars {
namespace windowing {
struct Renderer;
struct Texture;
}
namespace widgets {

/**
 * @brief An interface for all drawable widgets like: video, html, text etc.
 */
struct Widget {

    Widget(windowing::Renderer& renderer);

    virtual ~Widget() = default;

    /**
     * @brief Updates an internal buffer with new content
     * @return true if there is an update, false if buffer cannot be updated (video finished etc)
     */
    virtual bool update() const noexcept = 0;

    /**
     * @brief Schedules a repaint of buffer
     */
    virtual void render() noexcept;

    virtual bool event(const windowing::EventVariant& event) noexcept;

    std::int32_t x() const noexcept { return _x; }
    std::int32_t y() const noexcept { return _y; }
    std::uint32_t width() const noexcept;
    std::uint32_t height() const noexcept;

    std::uint32_t z() const noexcept { return _z; }

    virtual void move(std::int32_t x, std::int32_t y);

    void setZ(std::uint32_t z) { _z = z; }

    void addBackground() noexcept;

protected:
    void requestRefresh();

    windowing::Renderer& _parentRenderer;
    std::int32_t _x;
    std::int32_t _y;
    std::uint32_t _width;
    std::uint32_t _height;
    std::uint32_t _z;

    std::unique_ptr<windowing::Texture> _texture;
    std::unique_ptr<windowing::Texture> _background;
};
} // namespace widgets
} // namespace mars

#endif /* end of include guard: WIDGET_H_G5T74RQZ */
