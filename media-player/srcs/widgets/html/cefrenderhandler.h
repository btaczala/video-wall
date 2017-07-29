#ifndef CEFRENDERHANDLER_H_YRSXP9QE
#define CEFRENDERHANDLER_H_YRSXP9QE

#include <cef_render_handler.h>

namespace mars {
namespace windowing {
struct IRenderer;
struct ITexture;
} // namespace windowing

namespace webengine {
struct RenderHandler : public CefRenderHandler {
    RenderHandler(windowing::IRenderer* renderer, int w, int h);
    ~RenderHandler();

    bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect) override;

    void OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList& dirtyRects, const void* buffer,
        int w, int h) override;

    void render(std::uint32_t x, std::uint32_t y);

private:
    const std::unique_ptr<windowing::ITexture> _renderingTexture;
    IMPLEMENT_REFCOUNTING(RenderHandler);
};
} // namespace webengine
} // namespace mars

#endif /* end of include guard: CEFRENDERHANDLER_H_YRSXP9QE */
