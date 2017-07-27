#include "videowidget.h"
#include "irenderer.h"
#include "itexture.h"
#include "ivideorenderer.h"

#include "log.hpp"

namespace mars {
namespace widgets {

VideoWidget::VideoWidget(
    const std::string& filename, windowing::IRenderer& renderer, rendering::IVideoBackend& videoBackend)
    : _renderer(renderer)
    , _video(videoBackend.createVideo(filename))
    , _texture(_renderer.createTexture(_video->info().width, _video->info().height, windowing::PixelFormat::IYUV))
{
    mars_debug("VideoWidget video size {}x{}", _video->info().width, _video->info().height);
}

bool VideoWidget::update() noexcept
{
    auto frame = _video->frame();
    if (frame) {
        const auto in = _video->info();
        _texture->UpdateYUVTexture(windowing::Rect{ 0, 0, in.width, in.height }, frame->planes[0].pixels,
            frame->planes[0].linesize, frame->planes[1].pixels, frame->planes[1].linesize, frame->planes[2].pixels,
            frame->planes[2].linesize);
    }

    return !!frame;
}
void VideoWidget::render() noexcept { _texture->render(); }

void VideoWidget::moveTo(std::uint16_t newX, std::uint16_t newY) noexcept {}
} // widgets
} // mars
