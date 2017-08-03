#include "textwidget.h"
#include "ifont.h"
#include "itexture.h"
#include "log.hpp"
#include "renderer.h"

#include <linux/limits.h>

#include <boost/filesystem.hpp>
namespace {

using namespace boost::filesystem;

const std::vector<std::string> kFontPaths{ "/usr/share/fonts", current_path().string() };

std::string fontPath(const std::string& fontName)
{
    if (fontName.empty()) {
        throw std::runtime_error("font name cannot be empty");
    }
    mars_debug_(rendering, "Searching for font {}", fontName);
    path fontPath{ fontName };

    if (exists(fontPath)) {
        mars_debug_(rendering, "Font {} exists", fontName);
        return fontPath.string();
    }

    for (const auto& p : kFontPaths) {
        if (exists(p / fontPath)) {
            return (p / fontPath).string();
        }
    }

    throw std::runtime_error(fmt::format("Unable to find font {}", fontName));
}
} // namespace

namespace mars {
namespace widgets {
TextWidget::TextWidget(
    windowing::Renderer& renderer, const std::string& text, const std::string& font, std::uint32_t textSize)
    : Widget(renderer)
    , _text(text)
    , _font(renderer.createFont(fontPath(font), textSize))
    , _textTexture(_font->renderText(text))
{
    mars_info("Created TextWidget with text = {}, font = {}, size = {}, _texture = {}", text, font, textSize,
        static_cast<void*>(_textTexture.get()));
}

void TextWidget::render() noexcept { _textTexture->render(_x, _y); }

} // namespace widgets
} // namespace mars
