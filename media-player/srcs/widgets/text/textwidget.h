#ifndef TEXTWIDGET_H_M6JZGUL4
#define TEXTWIDGET_H_M6JZGUL4

#include "ifont.h"
#include "widget.h"
#include <string>

namespace mars {
namespace windowing {
struct Renderer;
struct ITexture;
} // windowing
namespace widgets {
struct TextWidget : public Widget {
    TextWidget(windowing::Renderer& renderer, const std::string& text, const std::string& font, std::uint32_t textSize);

    bool update() const noexcept override { return true; }
    void render() noexcept override;

private:
    const std::string _text;
    const std::unique_ptr<windowing::IFont> _font;
    const std::unique_ptr<windowing::ITexture> _textTexture;
};
} // widgets
} // mars

#endif /* end of include guard: TEXTWIDGET_H_M6JZGUL4 */
