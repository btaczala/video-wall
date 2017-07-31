#include "sdlfont.h"
#include "sdlrenderer.h"
#include "sdltexture.h"

namespace mars {
namespace windowing {

SDLFont::SDLFont(SDL_Renderer* renderer, const std::string& familyName, std::uint16_t size)
    : _renderer(renderer)
    , _font(TTF_OpenFont(familyName.c_str(), size))
{
}

std::unique_ptr<ITexture> SDLFont::renderText(const std::string& text) noexcept
{
    SDL_Color White = { 255, 255, 255, 0 };
    _surface.reset(TTF_RenderText_Solid(_font, text.c_str(), White));
    auto texture = SDL_CreateTextureFromSurface(_renderer, _surface.get());

    return std::make_unique<SDLTexture>(_renderer, texture);
}

} // namespace windowing
} // namespace mars
