#include "imagewidget.h"
#include "iimage.h"
#include "irenderer.h"

namespace mars {
namespace widgets {

ImageWidget::ImageWidget(const std::string& imagePath, windowing::IRenderer& renderer)
    : Widget(renderer)
    , _image(renderer.createImage(imagePath))
{
}

ImageWidget::~ImageWidget() {}

void ImageWidget::render() noexcept { _image->render(_x, _y); }

} // namespace widgets
} // namespace mars
