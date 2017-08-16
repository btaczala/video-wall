#include "texture.h"
#include <boost/optional.hpp>

namespace mars {
namespace windowing {

Texture::Texture() {}

void Texture::render(std::uint32_t x, std::uint32_t y) noexcept
{
    const auto si = size();
    if (_fullscreen) {
        render(boost::optional<Rect>{}, boost::optional<Rect>{});
    } else {
        render(Rect{ 0u, 0u, si.first, si.second }, Rect{ x, y, si.first, si.second });
    }
}

} // namespace windowing
} // namespace mars
