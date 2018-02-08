#ifndef RENDERERMOCK_HPP_AZXKKSZ0
#define RENDERERMOCK_HPP_AZXKKSZ0

#include "renderer.h"
#include "renderer_types.hpp"
#include "texture.h"
#include <boost/optional/optional_io.hpp>
#include <trompeloeil.hpp>

struct RendererMock : public mars::windowing::Renderer {

    std::unique_ptr<mars::windowing::Texture> createTexture(
        std::uint16_t w, std::uint16_t h, mars::windowing::PixelFormat p) noexcept override
    {
        return std::unique_ptr<mars::windowing::Texture>(createTextureProxy(w, h, p));
    }

    std::unique_ptr<mars::windowing::Texture> createImage(const std::string& name, bool fullscreen) override
    {
        return std::unique_ptr<mars::windowing::Texture>(createImageProxy(name, fullscreen));
    }

    std::unique_ptr<mars::windowing::Texture> createText(
        const std::string& text, const std::string& name, std::uint16_t size) noexcept override
    {
        return std::unique_ptr<mars::windowing::Texture>(createTextProxy(text, name, size));
    }

    boost::optional<mars::windowing::EventVariant> pollEvent() noexcept override
    {
        auto s = pollEventProxy();
        if (!s) {
            return boost::optional<mars::windowing::EventVariant>{};
        }

        return boost::optional<mars::windowing::EventVariant>{ *s };
    }

    MAKE_MOCK3(createTextureProxy,
        mars::windowing::Texture*(std::uint16_t, std::uint16_t, mars::windowing::PixelFormat), noexcept);
    MAKE_MOCK3(
        createTextProxy, mars::windowing::Texture*(const std::string, const std::string&, std::uint16_t), noexcept);
    MAKE_MOCK2(createImageProxy, mars::windowing::Texture*(const std::string&, bool));
    MAKE_MOCK0(clear, void(), noexcept, override);
    MAKE_MOCK0(render, void(), noexcept, override);
    MAKE_MOCK0(pollEventProxy, mars::windowing::EventVariant*(), noexcept);

    MAKE_MOCK1(requestRefresh, void(mars::widgets::Widget*), noexcept, override);
};

struct TextureMock : public mars::windowing::Texture {
    MAKE_CONST_MOCK0(size, mars::windowing::Texture::TextureSize(), noexcept, override);
    MAKE_MOCK2(put, void(const void*, const mars::windowing::Texture::TextureSize&), noexcept, override);
    MAKE_MOCK2(render,
        void(const boost::optional<mars::windowing::Rect>&, const boost::optional<mars::windowing::Rect>&), noexcept,
        override);
    MAKE_MOCK7(UpdateYUVTexture,
        void(const mars::windowing::Rect&, std::uint8_t*, int, std::uint8_t*, int, std::uint8_t*, int), noexcept,
        override);
};

#endif /* end of include guard: RENDERERMOCK_HPP_AZXKKSZ0 */
