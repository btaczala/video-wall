#ifndef VIDEOWIDGET_H_JMZKEF5D
#define VIDEOWIDGET_H_JMZKEF5D

#include "widget.h"
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

struct VideoWidget : public Widget {
    VideoWidget(const std::string& filename, windowing::Renderer& renderer, rendering::IVideoBackend& videoBackend);

    bool update() const noexcept override;
    void render() noexcept override;

    bool event(const windowing::EventVariant& event) noexcept override;

private:
    const std::unique_ptr<rendering::IVideoRenderer> _video;
};
} // namespace widgets
} // namespace mars

#endif /* end of include guard: VIDEOWIDGET_H_JMZKEF5D */
