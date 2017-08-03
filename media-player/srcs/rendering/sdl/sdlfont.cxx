#include "sdlfont.h"
#include "log.hpp"
#include "sdllogging.hpp"
#include "sdlrenderer.h"
#include "sdltexture.h"

#include <spdlog/fmt/fmt.h>

namespace mars {
namespace windowing {

SDLFont::SDLFont(SDL_Renderer* renderer, const std::string& familyName, std::uint16_t size)
    : _renderer(renderer)
    , _font(TTF_OpenFont(familyName.c_str(), size))
{
    mars_debug_(rendering, "Created font {}, ptr ={} ", familyName, static_cast<void*>(_font));

    if (!_font) {
        throw std::runtime_error(fmt::format("Unable to read font {} ec = {}", familyName, TTF_GetError()));
    }
}

SDLFont::~SDLFont()
{
    TTF_CloseFont(_font);
}

std::unique_ptr<ITexture> SDLFont::renderText(const std::string& text) noexcept
{
    SDL_Color White = { 255, 255, 255, 0 };
    _surface.reset(TTF_RenderText_Blended(_font, text.c_str(), White));
    auto texture = SDL_CreateTextureFromSurface(_renderer, _surface.get());

    mars_debug_(rendering, "Created texture {} from surface {}", static_cast<void*>(texture),
        static_cast<void*>(_surface.get()));

    mars_debug_(rendering, "{}", *(_surface.get()));

    return std::make_unique<SDLTexture>(_renderer, texture);
}

} // namespace windowing
} // namespace mars
