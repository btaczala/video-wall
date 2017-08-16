#include "imagewidget.h"
#include "texture.h"
#include "renderer.h"

namespace mars {
namespace widgets {

ImageWidget::ImageWidget(const std::string& imagePath, windowing::ImageType type, windowing::Renderer& renderer)
    : Widget(renderer)
{
    _texture = renderer.createImage(imagePath, type == windowing::ImageType::stretched);
}

ImageWidget::~ImageWidget() {}

} // namespace widgets
} // namespace mars
