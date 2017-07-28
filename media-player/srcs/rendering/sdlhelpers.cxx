#include "sdlhelpers.h"

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

// clang-format off
const std::map<std::uint32_t, translateFunction_t> kTranslator{
    {
        { SDL_QUIT, [](const auto&) { return mars::windowing::events::Quit{}; } },
        { SDL_KEYUP, keyboardEvent },
    }
};
// clang-format on
} // namespace

namespace sdl_helpers {
mars::windowing::EventVariant translateEvent(const SDL_Event& ev) { return kTranslator.at(ev.type)(ev); }
} // sdl_helpers
