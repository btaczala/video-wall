#include "sdlimage.h"
#include "sdltexture.h"

#include <SDL2/SDL_image.h>
#include <memory>

namespace mars {
namespace windowing {
SDLImage::SDLImage(const std::string& filename, SDL_Renderer* renderer)
    : _surface(IMG_Load(filename.c_str()))
    , _texture(std::make_unique<SDLTexture>(renderer, SDL_CreateTextureFromSurface(renderer, _surface.get())))
{
}

SDLImage::~SDLImage() {}

void SDLImage::render(std::uint32_t x, std::uint32_t y) noexcept { _texture->render(x, y); }
}
}
