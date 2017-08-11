#ifndef SDLFONT_H_GMS1BLQU
#define SDLFONT_H_GMS1BLQU

#include "itexture.h"
#include "sdlhelpers.h"

#include <cstdint>
#include <string>

#include <SDL2/SDL_ttf.h>

namespace mars {
namespace windowing {
struct SDLFont {
    SDLFont(SDL_Renderer* renderer, const std::string& familyName, std::uint16_t size);
    ~SDLFont();
    std::unique_ptr<ITexture> renderText(const std::string& text) noexcept;

private:
    SDL_Renderer* const _renderer;
    TTF_Font* const _font;
    sdl_helpers::SurfacePtr _surface;
};
} // windowing
} // mars

#endif /* end of include guard: SDLFONT_H_GMS1BLQU */
