#ifndef TEXTURE_H_LFG1JAQW
#define TEXTURE_H_LFG1JAQW

#include "renderer_types.hpp"

#include <boost/optional/optional_fwd.hpp>
#include <cstdint>
#include <utility>

namespace mars {
namespace windowing {

/**
 * @brief
 */
struct Texture {
    using TextureSize = std::pair<std::uint16_t, std::uint16_t>;
    Texture();
    virtual ~Texture() = default;
    virtual TextureSize size() const noexcept = 0;

    virtual void put(const void* buffer, const TextureSize& size) noexcept = 0;

    virtual void render(std::uint32_t x, std::uint32_t y) noexcept;

    virtual void render(const boost::optional<Rect>& srcRect, const boost::optional<Rect>& dstRect) noexcept = 0;

    virtual void UpdateYUVTexture(const Rect&, std::uint8_t*, int, std::uint8_t*, int, std::uint8_t*, int) noexcept = 0;

    void setFullscreen(bool fullscreen) { _fullscreen = fullscreen; }

    void setRenderingOffset(const Rect& offset) { _renderingOffset = offset; }

protected:
    bool _fullscreen{ false };

    Rect _renderingOffset{ 0, 0, 0, 0 };
};
} // namespace windowing
} // namespace mars

#endif /* end of include guard: TEXTURE_H_LFG1JAQW */
