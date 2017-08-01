#ifndef RENDERER_TYPES_HPP_TH4HPV7T
#define RENDERER_TYPES_HPP_TH4HPV7T

#include <boost/variant.hpp>

namespace mars {
namespace widgets {
struct Widget;
} // namespace widgets
namespace windowing {

struct Rect {
    const std::uint32_t x;
    const std::uint32_t y;
    const std::uint32_t w;
    const std::uint32_t h;
};

enum class PixelFormat { Unknown = 0, IYUV };

namespace events {
struct Quit {
};
struct Keyboard {
    enum class Key { Unknown = 0, Space };
    Key key{ Key::Unknown };
};

struct Refresh {
    widgets::Widget* widget;
};

} // events

using EventVariant = boost::variant<events::Quit, events::Keyboard, events::Refresh>;

} // namespace windowing
} // namespace mars

#endif /* end of include guard: RENDERER_TYPES_HPP_TH4HPV7T */
