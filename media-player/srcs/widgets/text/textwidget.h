#ifndef TEXTWIDGET_H_M6JZGUL4
#define TEXTWIDGET_H_M6JZGUL4

#include "widget.h"
#include <string>

namespace mars {
namespace windowing {
struct IRenderer;
struct ITexture;
} // windowing
namespace widgets {
struct TextWidget : public Widget {
    TextWidget(windowing::IRenderer& renderer, const std::string& text, const std::string& font);

    bool update() const noexcept override { return false; }
    void render() noexcept override;

private:
    const std::string _text;
    const std::string _font;
};
} // widgets
} // mars

#endif /* end of include guard: TEXTWIDGET_H_M6JZGUL4 */
