#ifndef RENDERERMOCK_HPP_AZXKKSZ0
#define RENDERERMOCK_HPP_AZXKKSZ0

#include "irenderer.h"
#include "itexture.h"
#include "renderer_types.hpp"
#include <trompeloeil.hpp>

struct RendererMock : public mars::windowing::IRenderer {

    std::unique_ptr<mars::windowing::ITexture> createTexture(
        std::uint16_t w, std::uint16_t h, mars::windowing::PixelFormat p) noexcept override
    {
        return std::unique_ptr<mars::windowing::ITexture>(createTextureProxy(w, h, p));
    }

    MAKE_MOCK3(createTextureProxy,
        mars::windowing::ITexture*(std::uint16_t, std::uint16_t, mars::windowing::PixelFormat), noexcept, override);
    MAKE_MOCK0(clear, void(), noexcept, override);
    MAKE_MOCK0(render, void(), noexcept, override);
    MAKE_MOCK1(addWidget, void(const std::shared_ptr<mars::widgets::Widget>&), override);

    MAKE_MOCK1(requestRefresh, void(mars::widgets::Widget*), noexcept, override);
};

struct TextureMock : public mars::windowing::ITexture {
    MAKE_CONST_MOCK0(size, mars::windowing::ITexture::TextureSize(), noexcept, override);
    MAKE_MOCK2(put, void(const void*, const mars::windowing::ITexture::TextureSize&), noexcept, override);
    MAKE_MOCK2(render, void(std::uint32_t x, std::uint32_t y), noexcept, override);
    MAKE_MOCK7(UpdateYUVTexture,
        void(const mars::windowing::Rect&, std::uint8_t*, int, std::uint8_t*, int, std::uint8_t*, int), noexcept,
        override);
};

#endif /* end of include guard: RENDERERMOCK_HPP_AZXKKSZ0 */
