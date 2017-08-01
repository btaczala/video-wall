#ifndef RENDERERMOCK_HPP_AZXKKSZ0
#define RENDERERMOCK_HPP_AZXKKSZ0

#include "ifont.h"
#include "iimage.h"
#include "itexture.h"
#include "renderer.h"
#include "renderer_types.hpp"
#include <trompeloeil.hpp>

struct RendererMock : public mars::windowing::Renderer {

    std::unique_ptr<mars::windowing::ITexture> createTexture(
        std::uint16_t w, std::uint16_t h, mars::windowing::PixelFormat p) noexcept override
    {
        return std::unique_ptr<mars::windowing::ITexture>(createTextureProxy(w, h, p));
    }
    std::unique_ptr<mars::windowing::IFont> createFont(const std::string& name, std::uint16_t size) noexcept override
    {
        return std::unique_ptr<mars::windowing::IFont>(createFontProxy(name, size));
    }
    std::unique_ptr<mars::windowing::IImage> createImage(const std::string& name) noexcept
    {
        return std::unique_ptr<mars::windowing::IImage>(createImageProxy(name));
    }

    MAKE_MOCK3(createTextureProxy,
        mars::windowing::ITexture*(std::uint16_t, std::uint16_t, mars::windowing::PixelFormat), noexcept);
    MAKE_MOCK2(createFontProxy, mars::windowing::IFont*(const std::string&, std::uint16_t), noexcept);
    MAKE_MOCK1(createImageProxy, mars::windowing::IImage*(const std::string&), noexcept);
    MAKE_MOCK0(clear, void(), noexcept, override);
    MAKE_MOCK0(render, void(), noexcept, override);
    MAKE_MOCK0(pollEvent, boost::optional<mars::windowing::EventVariant>(), noexcept, override);

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

struct FontMock : public mars::windowing::IFont {
    std::unique_ptr<mars::windowing::ITexture> renderText(const std::string& text) noexcept override
    {
        return std::unique_ptr<mars::windowing::ITexture>(renderTextProxy(text));
    }
    MAKE_MOCK1(renderTextProxy, mars::windowing::ITexture*(const std::string&), noexcept);
};

struct ImageMock : public mars::windowing::IImage {
};

#endif /* end of include guard: RENDERERMOCK_HPP_AZXKKSZ0 */
