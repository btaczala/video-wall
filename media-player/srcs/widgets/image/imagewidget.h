#ifndef IMAGEWIDGET_H_SKFR8KQO
#define IMAGEWIDGET_H_SKFR8KQO

#include "widget.h"
#include <string>

namespace mars {
namespace windowing {
enum class ImageType { normal = 0, stretched };

struct Renderer;
struct ITexture;
} // namespace windowing

namespace widgets {

struct ImageWidget : public Widget {
    ImageWidget(const std::string& imagePath, windowing::ImageType type, windowing::Renderer& renderer);
    ~ImageWidget();

    bool update() const noexcept override { return true; }

    void render() noexcept override;

private:
    const std::unique_ptr<windowing::ITexture> _image;
};
} // namespace widgets
} // namespace mars

#endif /* end of include guard: IMAGEWIDGET_H_SKFR8KQO */
