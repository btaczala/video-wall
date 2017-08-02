#ifndef SDLIMAGE_H_JHTCOBBW
#define SDLIMAGE_H_JHTCOBBW

#include "iimage.h"
#include "sdlhelpers.h"
#include <string>

struct SDL_Renderer;

namespace mars {
namespace windowing {
struct ITexture;
struct SDLImage : public IImage {
    SDLImage(const std::string& filename, bool fullscreen, SDL_Renderer* renderer);
    ~SDLImage();

    void render(std::uint32_t x, std::uint32_t y) noexcept override;

private:
    const sdl_helpers::SurfacePtr _surface;
    const std::unique_ptr<ITexture> _texture;
};
}
}

#endif /* end of include guard: SDLIMAGE_H_JHTCOBBW */
