#include "widget.h"
#include "renderer.h"
#include "log.hpp"
#include "renderer_types.hpp"

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
} // namespace widgets
} // namespace mars
