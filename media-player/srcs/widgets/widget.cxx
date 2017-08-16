#include "widget.h"
#include "log.hpp"
#include "renderer.h"
#include "renderer_types.hpp"

#include "texture.h"

namespace mars {
namespace widgets {

Widget::Widget(windowing::Renderer& renderer)
    : _parentRenderer(renderer)
    , _x(0)
    , _y(0)
    , _width(0)
    , _height(0)
    , _z(0)
{
    mars_debug_(ui, "Created widget {}", static_cast<void*>(this));
}

void Widget::render() noexcept
{
    mars_debug_(ui, "[{}] Widget::render()", static_cast<void*>(this));
    if (_background) {
        _background->render(windowing::Rect{ _x, _y, _width, _height });
    }

    if (BOOST_LIKELY(_texture != nullptr)) {
        _texture->render(windowing::Rect{ _x, _y, _width, _height });
    }
}

bool Widget::event(const windowing::EventVariant& event) noexcept
{
    mars_debug_(ui, "Default event handler will do nothing");
    return false;
}

void Widget::requestRefresh()
{
    mars_debug_(ui, "Scheduling refresh for widget {}", static_cast<void*>(this));
    _parentRenderer.requestRefresh(this);
}

void Widget::move(std::int32_t x, std::int32_t y)
{
    mars_debug_(ui, "moving widget {}x{}", x, y);
    _x = x;
    _y = y;

    requestRefresh();
}

void Widget::addBackground() noexcept
{
    mars_debug_(ui, "Adding background for Widget {}", static_cast<void*>(this));
    _background = _parentRenderer.createTexture(width(), height(), mars::windowing::PixelFormat::Unknown);
}

std::uint32_t Widget::width() const noexcept { return _width; }

std::uint32_t Widget::height() const noexcept { return _height; }

void Widget::setRect(const windowing::Rect& r)
{
    mars_info_(ui, "[{}] Changin size {}", static_cast<void*>(_texture.get()), r);
    _x = r.x;
    _y = r.y;
    _width = r.w;
    _height = r.h;
}

} // namespace widgets
} // namespace mars
