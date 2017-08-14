#ifndef RENDERER_TYPES_HPP_TH4HPV7T
#define RENDERER_TYPES_HPP_TH4HPV7T

#include "events.hpp"

#include <boost/variant.hpp>
#include <iostream>

namespace mars {
namespace windowing {

struct Rect {
    std::uint32_t x;
    std::uint32_t y;
    std::uint32_t w;
    std::uint32_t h;
};
inline std::ostream& operator<<(std::ostream& os, const Rect& r) { return os; }

enum class PixelFormat { Unknown = 0, IYUV };

using EventVariant = boost::variant<events::Quit, events::Keyboard, events::Refresh, events::Window>;

} // namespace windowing
} // namespace mars

#endif /* end of include guard: RENDERER_TYPES_HPP_TH4HPV7T */
