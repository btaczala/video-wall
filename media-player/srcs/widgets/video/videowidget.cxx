#include "videowidget.h"
#include "irenderer.h"
#include "itexture.h"
#include "ivideorenderer.h"

#include "renderer_types.hpp"

#include "log.hpp"

namespace {
struct video_event_visitor : public boost::static_visitor<bool> {
    template <typename T>
    bool operator()(T&& t,
        typename std::enable_if<!std::is_same<T, mars::windowing::events::Keyboard>::value>::type* = nullptr) const
    {
        return false;
    }

    bool operator()(const mars::windowing::events::Keyboard& t) const
    {
        mars_debug("Keyboard event received");
        return true;
    }
};
} // namespace

namespace mars {
namespace widgets {

VideoWidget::VideoWidget(
    const std::string& filename, windowing::IRenderer& renderer, rendering::IVideoBackend& videoBackend)
    : _renderer(renderer)
    , _video(videoBackend.createVideo(filename))
    , _texture(_renderer.createTexture(_video->info().width, _video->info().height, windowing::PixelFormat::IYUV))
{
    _x = 0;
    _y = 0;
    _width = _video->info().width; 
    _height = _video->info().height;
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

bool VideoWidget::event(const windowing::EventVariant& event) noexcept
{
    return boost::apply_visitor(video_event_visitor(), event);
}

} // namespace widgets
} // namespace mars
