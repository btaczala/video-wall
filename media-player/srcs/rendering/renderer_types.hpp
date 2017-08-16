#ifndef RENDERER_TYPES_HPP_TH4HPV7T
#define RENDERER_TYPES_HPP_TH4HPV7T

#include "events.hpp"

#include <boost/variant.hpp>
#include <iostream>

namespace mars {
namespace windowing {

struct Rect {
    std::int32_t x;
    std::int32_t y;
    std::int32_t w;
    std::int32_t h;
};
inline std::ostream& operator<<(std::ostream& os, const Rect& c) { 
    return os << "windowing::Rect {" << c.x << "," << c.y << "," << c.w << "," << c.h << "}";
}

enum class PixelFormat { Unknown = 0, IYUV };

using EventVariant = boost::variant<events::Quit, events::Keyboard, events::Refresh, events::Window>;

} // namespace windowing
} // namespace mars

#endif /* end of include guard: RENDERER_TYPES_HPP_TH4HPV7T */
