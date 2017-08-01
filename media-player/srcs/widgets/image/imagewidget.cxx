#include "imagewidget.h"
#include "iimage.h"
#include "renderer.h"

namespace mars {
namespace widgets {

ImageWidget::ImageWidget(const std::string& imagePath, windowing::Renderer& renderer)
    : Widget(renderer)
    , _image(renderer.createImage(imagePath))
{
}

ImageWidget::~ImageWidget() {}

void ImageWidget::render() noexcept { _image->render(_x, _y); }

} // namespace widgets
} // namespace mars
