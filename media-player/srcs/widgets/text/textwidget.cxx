#include "textwidget.h"
#include "ifont.h"
#include "renderer.h"
#include "itexture.h"

namespace mars {
namespace widgets {
TextWidget::TextWidget(
    windowing::Renderer& renderer, const std::string& text, const std::string& font, std::uint32_t textSize)
    : Widget(renderer)
    , _text(text)
    , _font(renderer.createFont(font, textSize))
    , _textTexture(_font->renderText(text))
{
}

void TextWidget::render() noexcept
{
    _textTexture->render(_x, _y);
}

} // namespace widgets
} // namespace mars
