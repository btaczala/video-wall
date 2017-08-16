#include "texture.h"
#include <boost/optional.hpp>

namespace mars {
namespace windowing {

Texture::Texture() {}

void Texture::render(const Rect& r) noexcept
{
    const auto si = size();
    if (_fullscreen) {
        render(boost::optional<Rect>{}, boost::optional<Rect>{});
    } else {
        render(Rect{ 0, 0, si.first, si.second }, r);
    }
}

} // namespace windowing
} // namespace mars
