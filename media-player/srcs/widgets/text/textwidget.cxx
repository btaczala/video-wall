#include "textwidget.h"
#include "iconfigurationmanager.h"
#include "texture.h"
#include "log.hpp"
#include "renderer.h"

#include <boost/filesystem.hpp>
#include <boost/variant/get.hpp>
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
    , _haveBackground(false)
{
    _texture = renderer.createText(text, fontPath(font, cm), textSize);
    mars_info_(ui, "Created TextWidget with text = {}, font = {}, size = {}, _texture = {}", text, font, textSize,
        static_cast<void*>(_texture.get()));
    mars_debug_(ui, "texture size={}x{}", _texture->size().first, _texture->size().second);
}

bool TextWidget::event(const windowing::EventVariant& event) noexcept
{
    auto pEvent = boost::get<windowing::events::Keyboard>(&event);
    if (pEvent) {
        mars_debug_(ui, "TextWidget::event {}", static_cast<int>(pEvent->key));
        if (pEvent->key == windowing::events::Keyboard::Key::Space) {
            mars_debug_(ui, "Received space key");
            offset += 10;
            auto w = _texture->size().first;

            if (offset > w) {
                offset = 0;
            }
            _texture->setRenderingOffset(windowing::Rect{ offset, 0, 0, 0 });
            requestRefresh();
            return true;
        }
    }

    return false;
}

} // namespace widgets
} // namespace mars
