#include "widget.h"
#include "log.hpp"
#include "renderer.h"
#include "renderer_types.hpp"

#include "itexture.h"

namespace mars {
namespace widgets {

Widget::Widget(windowing::Renderer& renderer)
    : _parentRenderer(renderer)
    , _x(0)
    , _y(0)
    , _z(0)
{
    mars_debug_(ui, "Created widget {}", static_cast<void*>(this));
}

void Widget::render() noexcept
{
    mars_debug_(ui, "[{}] Widget::render()", static_cast<void*>(this));
    if (_background) {
        _background->render(_x, _y);
    }

    if (BOOST_LIKELY(_texture != nullptr)) {
        _texture->render(_x, _y);
    }
}

bool Widget::event(const windowing::EventVariant& event) noexcept { return false; }

void Widget::requestRefresh()
{
    mars_debug_(ui, "Scheduling refresh for widget {}", static_cast<void*>(this));
    _parentRenderer.requestRefresh(this);
}

void Widget::move(std::uint32_t x, std::uint32_t y)
{
    _x = x;
    _y = y;
}

void Widget::addBackground() noexcept
{
    mars_debug_(ui, "Adding background for Widget {}", static_cast<void*>(this));
    _background = _parentRenderer.createTexture(width(), height(), mars::windowing::PixelFormat::Unknown);
}

std::uint32_t Widget::width() const noexcept
{
    if (!_texture) {
        return std::numeric_limits<std::uint32_t>::max();
    }
    return _texture->size().first;
}

std::uint32_t Widget::height() const noexcept
{
    if (!_texture) {
        return std::numeric_limits<std::uint32_t>::max();
    }
    return _texture->size().second;
}

} // namespace widgets
} // namespace mars
