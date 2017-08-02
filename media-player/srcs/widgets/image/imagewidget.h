#ifndef IMAGEWIDGET_H_SKFR8KQO
#define IMAGEWIDGET_H_SKFR8KQO

#include "iimage.h"
#include "widget.h"
#include <string>

namespace mars {
namespace windowing {
struct Renderer;
struct IImage;
}
namespace widgets {

struct ImageWidget : public Widget {
    ImageWidget(const std::string& imagePath, windowing::ImageType type, windowing::Renderer& renderer);
    ~ImageWidget();

    bool update() const noexcept override { return true; }

    void render() noexcept override;

private:
    const std::unique_ptr<windowing::IImage> _image;
};
} // namespace widgets
} // namespace mars

#endif /* end of include guard: IMAGEWIDGET_H_SKFR8KQO */
