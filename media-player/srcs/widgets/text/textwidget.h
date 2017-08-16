#ifndef TEXTWIDGET_H_M6JZGUL4
#define TEXTWIDGET_H_M6JZGUL4

#include "widget.h"
#include <string>

namespace mars {
namespace windowing {
struct Renderer;
struct Texture;
} // windowing

namespace core {
struct IConfigurationManager;

} // namespace core

namespace widgets {
struct TextWidget : public Widget {
    TextWidget(const std::string& text, const std::string& font, std::uint32_t textSize, windowing::Renderer& renderer,
        core::IConfigurationManager& cm);

    bool update() const noexcept override { return true; }
    bool event(const windowing::EventVariant& event) noexcept override;

private:
    const std::string _text;
    const bool _haveBackground;
    std::uint32_t offset{ 0 };
};
} // namespace widgets
} // namespace mars

#endif /* end of include guard: TEXTWIDGET_H_M6JZGUL4 */
