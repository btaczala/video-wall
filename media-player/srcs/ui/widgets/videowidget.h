#ifndef VIDEOWIDGET_H_JMZKEF5D
#define VIDEOWIDGET_H_JMZKEF5D

#include "iwidget.h"
#include <memory>

namespace mars {

namespace rendering {
struct IVideoRenderer;
struct IVideoBackend;
} // rendering

namespace ui {
struct IRenderer;
struct ITexture;
namespace widgets {

struct VideoWidget : public IWidget {
    VideoWidget(const std::string& filename, IRenderer& renderer, rendering::IVideoBackend& videoBackend);

    bool update() noexcept override;
    void render() noexcept override;
    void moveTo(std::uint16_t newX, std::uint16_t newY) noexcept override;

private:
    IRenderer& _renderer;
    const std::unique_ptr<rendering::IVideoRenderer> _video;
    const std::unique_ptr<ITexture> _texture;
};
} // widgets
} // ui
} // mars

#endif /* end of include guard: VIDEOWIDGET_H_JMZKEF5D */
