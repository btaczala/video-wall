#include "textwidget.h"
#include "irenderer.h"

namespace mars {
namespace widgets {
TextWidget::TextWidget(windowing::IRenderer& renderer, const std::string& text, const std::string& font)
    : Widget(renderer)
    , _text(text)
    , _font(font)
{
}

void TextWidget::render() noexcept
{
    // TODO: Implement me
}

} // widgets
} // mars
