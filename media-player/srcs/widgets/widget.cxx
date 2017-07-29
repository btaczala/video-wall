#include "widget.h"
#include "irenderer.h"
#include "log.hpp"
#include "renderer_types.hpp"

namespace mars {
namespace widgets {

Widget::Widget(windowing::IRenderer& renderer)
    : _parentRenderer(renderer)
{
}

bool Widget::event(const windowing::EventVariant& event) noexcept { return false; }

void Widget::requestRefresh()
{
    mars_debug_(ui, "Scheduling refresh for widget {}", static_cast<void*>(this));
    _parentRenderer.requestRefresh();
}

void Widget::move(std::uint32_t x, std::uint32_t y)
{
    _x = x;
    _y = y;
}
} // namespace widgets
} // namespace mars
