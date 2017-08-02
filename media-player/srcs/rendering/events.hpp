#ifndef EVENTS_HPP_K1CTAMSI
#define EVENTS_HPP_K1CTAMSI

namespace mars {
namespace widgets {
struct Widget;
} // namespace widgets
namespace windowing {
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

struct Window {
    enum class Type {
        Unknown=0,
        Shown,
        Hidden,
        Exposed,
        Resized,
        Minimized,
        Maximized,
        Restored,
        Enter,
        Leave,
        FocusGained,
        FocusLost
    };
    Type event;
};

} // events
} // namespace windowing
} // namespace mars

#endif /* end of include guard: EVENTS_HPP_K1CTAMSI */
