#ifndef CEFRENDERHANDLER_H_YRSXP9QE
#define CEFRENDERHANDLER_H_YRSXP9QE

#include <cef_render_handler.h>

namespace mars {
namespace ui {
struct IRenderer;
struct ITexture;
}

namespace webengine {
struct RenderHandler : public CefRenderHandler {
    RenderHandler(ui::IRenderer* renderer, int w, int h);
    ~RenderHandler();
    bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect) override;

    void OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList& dirtyRects, const void* buffer,
        int w, int h) override;

    void render();

private:
    const std::unique_ptr<ui::ITexture> _renderingTexture;
    IMPLEMENT_REFCOUNTING(RenderHandler);
};
}
}

#endif /* end of include guard: CEFRENDERHANDLER_H_YRSXP9QE */
