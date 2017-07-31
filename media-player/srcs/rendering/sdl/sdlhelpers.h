#ifndef SDLHELPERS_HPP_WQF0GKRU
#define SDLHELPERS_HPP_WQF0GKRU

#include "renderer_types.hpp"
#include <SDL.h>

namespace sdl_helpers {
struct deleter {
    void operator()(SDL_Texture* ptr)
    {
        if (ptr)
            SDL_DestroyTexture(ptr);
    }
    void operator()(SDL_Renderer* ptr)
    {
        if (ptr)
            SDL_DestroyRenderer(ptr);
    }
    void operator()(SDL_Surface* ptr)
    {
        if (ptr)
            SDL_FreeSurface(ptr);
    }
};
using TexturePtr = std::unique_ptr<SDL_Texture, deleter>;
using RendererPtr = std::unique_ptr<SDL_Renderer, deleter>;
using SurfacePtr = std::unique_ptr<SDL_Surface, deleter>;

mars::windowing::EventVariant translateEvent(const SDL_Event& ev);

} // namespace sdl_helpers

#endif /* end of include guard: SDLHELPERS_HPP_WQF0GKRU */
