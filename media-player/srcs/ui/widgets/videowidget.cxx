#include "videowidget.h"
#include "irenderer.h"
#include "ivideorenderer.h"

namespace mars {
namespace ui {
namespace widgets {

VideoWidget::VideoWidget(const std::string& filename, IRenderer& renderer, rendering::IVideoBackend& videoBackend)
    : _renderer(renderer)
    , _video(videoBackend.createVideo(filename))
    , _texture(_renderer.createTexture(_video->info().width, _video->info().height, PixelFormat::IYUV))
{
}

bool VideoWidget::update()
{
    auto frame = _video->frame();
    if (frame) {
        const auto in = _video->info();
        _texture->UpdateYUVTexture(Rect{ 0, 0, in.width, in.height }, frame->planes[0].pixels,
            frame->planes[0].linesize, frame->planes[1].pixels, frame->planes[1].linesize, frame->planes[2].pixels,
            frame->planes[2].linesize);
    }

    return !!frame;
}
void VideoWidget::render() { _texture->render(); }
}
}
}
