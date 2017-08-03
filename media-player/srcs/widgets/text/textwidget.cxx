#include "textwidget.h"
#include "iconfigurationmanager.h"
#include "ifont.h"
#include "itexture.h"
#include "log.hpp"
#include "renderer.h"

#include <linux/limits.h>

#include <boost/filesystem.hpp>
namespace {

using namespace boost::filesystem;

std::string fontPath(const std::string& fontName, mars::core::IConfigurationManager& configManager)
{
    auto fontPaths = configManager.fontsPaths();

    fontPaths.push_back(current_path().string());

    if (fontName.empty()) {
        mars_error_(rendering, "Font name cannot be empty");
        throw std::runtime_error("font name cannot be empty");
    }

    mars_debug_(rendering, "Searching for font {}", fontName);
    path fontPath{ fontName };

    if (exists(fontPath)) {
        mars_debug_(rendering, "Font {} exists", fontName);
        return fontPath.string();
    }

    for (const auto& p : fontPaths) {
        if (exists(p / fontPath)) {
            return (p / fontPath).string();
        }
    }

    mars_error_(rendering, "Unable to find font {}", fontName);
    throw std::runtime_error(fmt::format("Unable to find font {}", fontName));
}
} // namespace

namespace mars {
namespace widgets {
TextWidget::TextWidget(const std::string& text, const std::string& font, std::uint32_t textSize,
    windowing::Renderer& renderer, core::IConfigurationManager& cm)
    : Widget(renderer)
    , _text(text)
    , _font(renderer.createFont(fontPath(font, cm), textSize))
    , _textTexture(_font->renderText(text))
{
    mars_info("Created TextWidget with text = {}, font = {}, size = {}, _texture = {}", text, font, textSize,
        static_cast<void*>(_textTexture.get()));
}

void TextWidget::render() noexcept { _textTexture->render(_x, _y); }

} // namespace widgets
} // namespace mars
