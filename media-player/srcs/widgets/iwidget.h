#ifndef IWIDGET_H_G5T74RQZ
#define IWIDGET_H_G5T74RQZ

#include <cstdint>

#include "renderer_types.hpp"

namespace mars {
namespace widgets {

/**
 * @brief An interface for all drawable widgets like: video, html, text etc.
 */
struct IWidget {
    virtual ~IWidget() = default;

    /**
     * @brief Updates an internal buffer with new content
     * @return true if there is an update, false if buffer cannot be updated (video finished etc)
     */
    virtual bool update() noexcept = 0;

    /**
     * @brief Schedules a repaint of buffer
     */
    virtual void render() noexcept = 0;

    virtual void moveTo(std::uint16_t newX, std::uint16_t newY) = 0;

    virtual bool event(const windowing::EventVariant& event) noexcept = 0;
};
} // namespace widgets
} // namespace mars

#endif /* end of include guard: IWIDGET_H_G5T74RQZ */
