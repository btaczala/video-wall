#ifndef VIDEOWIDGET_H_JMZKEF5D
#define VIDEOWIDGET_H_JMZKEF5D

#include <memory>

namespace mars {

namespace rendering {
struct IVideoRenderer;
struct IVideoBackend;
}

namespace ui {
struct IRenderer;
struct ITexture;
namespace widgets {
struct VideoWidget {
    VideoWidget(const std::string& filename, IRenderer& renderer, rendering::IVideoBackend& videoBackend);

    bool update();
    void render();

private:
    IRenderer& _renderer;
    const std::unique_ptr<rendering::IVideoRenderer> _video;
    const std::unique_ptr<ITexture> _texture;
};
}
}
}

#endif /* end of include guard: VIDEOWIDGET_H_JMZKEF5D */
