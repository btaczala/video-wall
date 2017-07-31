#include "textwidget.h"
#include "ifont.h"
#include "irenderer.h"
#include "itexture.h"

namespace mars {
namespace widgets {
TextWidget::TextWidget(windowing::IRenderer& renderer, const std::string& text, const std::string& font)
    : Widget(renderer)
    , _text(text)
    , _font(renderer.createFont(font, 10))
    , _textTexture(_font->renderText(text))
{
}

void TextWidget::render() noexcept
{
    _textTexture->render(_x, _y);
}

} // namespace widgets
} // namespace mars
