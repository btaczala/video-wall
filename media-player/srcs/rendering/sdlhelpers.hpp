#ifndef SDLHELPERS_HPP_WQF0GKRU
#define SDLHELPERS_HPP_WQF0GKRU

#include <SDL.h>

namespace mars {
namespace ui {
namespace sdl_helpers {
struct deleter {
    void operator()(SDL_Texture* ptr) {
        if (ptr) SDL_DestroyTexture(ptr);
    }
    void operator()(SDL_Renderer* ptr) {
        if (ptr) SDL_DestroyRenderer(ptr);
    }
};
using TexturePtr = std::unique_ptr<SDL_Texture, deleter>;
using RendererPtr = std::unique_ptr<SDL_Renderer, deleter>;
}
}
};

#endif /* end of include guard: SDLHELPERS_HPP_WQF0GKRU */
