#include "sdlhelpers.h"
#include "log.hpp"

#include <functional>
#include <map>

namespace {
using translateFunction_t = std::function<mars::windowing::EventVariant(const SDL_Event&)>;
using namespace mars::windowing;

events::Keyboard keyboardEvent(const SDL_Event& ev)
{
    using namespace mars::windowing::events;
    Keyboard::Key k{ Keyboard::Key::Unknown };
    if (ev.key.keysym.scancode == SDL_SCANCODE_SPACE) {
        k = Keyboard::Key::Space;
    }
    return Keyboard{ k };
}

events::Refresh refreshEvent(const SDL_Event& ev)
{
    return mars::windowing::events::Refresh{ reinterpret_cast<mars::widgets::Widget*>(ev.user.data1) };
}

events::Window windowEvent(const SDL_Event& ev)
{
    auto t = ev.window.event;
    mars_trace_(rendering, "window event window.type=0x{:x}", t);
    events::Window we;
    switch (t) {
    case SDL_WINDOWEVENT_SHOWN:
        we.event = events::Window::Type::Shown;
        break;
    case SDL_WINDOWEVENT_HIDDEN:
        we.event = events::Window::Type::Hidden;
        break;
    case SDL_WINDOWEVENT_EXPOSED:
        we.event = events::Window::Type::Exposed;
        break;
    case SDL_WINDOWEVENT_RESIZED:
        we.event = events::Window::Type::Resized;
        break;
    default:
        we.event = events::Window::Type::Unknown;
        break;
    }
    return we;
}

// clang-format off
const std::map<std::uint32_t, translateFunction_t> kTranslator{
    {
        { SDL_QUIT, [](const auto&) { return events::Quit{}; } },
        { SDL_KEYUP, keyboardEvent },
        { SDL_WINDOWEVENT, windowEvent },
        { SDL_USEREVENT, refreshEvent}, 
    }
};
// clang-format on
} // namespace

namespace sdl_helpers {
boost::optional<mars::windowing::EventVariant> translateEvent(const SDL_Event& ev)
{
    if (kTranslator.find(ev.type) != kTranslator.end()) {
        auto translated = kTranslator.at(ev.type)(ev);
        mars_debug_(rendering, "Translated event {:x} to {}", ev.type, translated.type().name());
        return translated;
    }

    mars_warn_(ui, "Unable to translate event 0x{:x}", ev.type);
    return boost::optional<mars::windowing::EventVariant>{};
}
} // namespace sdl_helpers
