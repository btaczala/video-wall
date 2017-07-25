#ifndef IRENDERER_H_HBWR9AKY
#define IRENDERER_H_HBWR9AKY

#include <cstdint>
#include <memory>
#include <utility>

namespace mars {
namespace ui {

struct ITexture {
    using TextureSize = std::pair<std::uint16_t, std::uint16_t>;
    virtual ~ITexture() = default;
    virtual TextureSize size() const noexcept = 0;

    virtual void put(const void* buffer, const TextureSize& size) noexcept = 0;

    virtual void render() noexcept = 0;
};

struct IRenderer {
    virtual ~IRenderer() = default;

    virtual std::unique_ptr<ITexture> createTexture(
        std::uint16_t width, std::uint16_t height) noexcept = 0;

    virtual void clear() noexcept = 0;

    virtual void render() noexcept = 0;
};
}
}

#endif /* end of include guard: IRENDERER_H_HBWR9AKY */
