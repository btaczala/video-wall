#include "imagewidget.h"
#include "renderer.h"
#include "texture.h"

namespace mars {
namespace widgets {

ImageWidget::ImageWidget(const std::string& imagePath, windowing::ImageType type, windowing::Renderer& renderer)
    : Widget(renderer)
{
    _texture = renderer.createImage(imagePath, type == windowing::ImageType::stretched);

    _width = _texture->size().first;
    _height = _texture->size().second;
}

ImageWidget::~ImageWidget() {}

} // namespace widgets
} // namespace mars
