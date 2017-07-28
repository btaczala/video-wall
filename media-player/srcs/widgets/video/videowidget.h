#ifndef VIDEOWIDGET_H_JMZKEF5D
#define VIDEOWIDGET_H_JMZKEF5D

#include "iwidget.h"
#include <memory>

namespace mars {

namespace rendering {
struct IVideoRenderer;
struct IVideoBackend;
} // namespace rendering

namespace windowing {
struct IRenderer;
struct ITexture;
} // namespace windowing
namespace widgets {

struct VideoWidget : public IWidget {
    VideoWidget(const std::string& filename, windowing::IRenderer& renderer, rendering::IVideoBackend& videoBackend);

    bool update() noexcept override;
    void render() noexcept override;
    void moveTo(std::uint16_t newX, std::uint16_t newY) noexcept override;

private:
    windowing::IRenderer& _renderer;
    const std::unique_ptr<rendering::IVideoRenderer> _video;
    const std::unique_ptr<windowing::ITexture> _texture;
};
} // namespace widgets
} // namespace mars

#endif /* end of include guard: VIDEOWIDGET_H_JMZKEF5D */
