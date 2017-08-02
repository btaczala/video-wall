#ifndef IIMAGE_H_LAC26GNE
#define IIMAGE_H_LAC26GNE

#include <cstdint>

namespace mars {
namespace windowing {

enum class ImageType { normal = 0, stretched };
struct IImage {
    virtual ~IImage() = default;
    virtual void render(std::uint32_t x, std::uint32_t y) noexcept = 0;
};
}
}

#endif /* end of include guard: IIMAGE_H_LAC26GNE */
