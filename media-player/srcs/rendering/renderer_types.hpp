#ifndef RENDERER_TYPES_HPP_TH4HPV7T
#define RENDERER_TYPES_HPP_TH4HPV7T

namespace mars {
namespace windowing {

struct Rect {
    const std::uint32_t x;
    const std::uint32_t y;
    const std::uint32_t w;
    const std::uint32_t h;
};

enum class PixelFormat { Unknown = 0, IYUV };

} // namespace windowing
} // namespace mars

#endif /* end of include guard: RENDERER_TYPES_HPP_TH4HPV7T */
