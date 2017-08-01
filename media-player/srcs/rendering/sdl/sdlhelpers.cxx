#include "sdlhelpers.h"
#include "log.hpp"

#include <functional>
#include <map>

namespace {
using translateFunction_t = std::function<mars::windowing::EventVariant(const SDL_Event&)>;

mars::windowing::events::Keyboard keyboardEvent(const SDL_Event& ev)
{
    using namespace mars::windowing::events;
    Keyboard::Key k{ Keyboard::Key::Unknown };
    if (ev.key.type == SDLK_SPACE) {
        k = Keyboard::Key::Space;
    }
    return Keyboard{ k };
}
mars::windowing::events::Refresh refreshEvent(const SDL_Event& ev)
{
    return mars::windowing::events::Refresh{ reinterpret_cast<mars::widgets::Widget*>(ev.user.data1) };
}

// clang-format off
const std::map<std::uint32_t, translateFunction_t> kTranslator{
    {
        { SDL_QUIT, [](const auto&) { return mars::windowing::events::Quit{}; } },
        { SDL_KEYUP, keyboardEvent },
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
        mars_trace_(rendering, "Translated event {:x} to {}", ev.type, translated.type().name());
        return translated;
    }

    mars_warn_(rendering, "Unable to translate event 0x{:x}", ev.type);
    return boost::optional<mars::windowing::EventVariant>{};
}
} // namespace sdl_helpers
