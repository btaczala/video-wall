#include "cefrenderhandler.h"
#include "log.hpp"

namespace mars {
namespace webengine {

RenderHandler::RenderHandler(const PaintCallback &cb, int w, int h): _cb(cb), _w(w), _h(h)
{
}

RenderHandler::~RenderHandler() {}

bool RenderHandler::GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect)
{
    rect = CefRect(0, 0, _w, _h);
    return true;
}

void RenderHandler::OnPaint(
    CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList& dirtyRects, const void* buffer, int w, int h)
{
    mars_trace_(html, "OnPaint({}, {}, {}, {}, {}, {}", static_cast<void*>(browser), type, dirtyRects.size(),
        static_cast<const void*>(buffer), w, h);
    _cb(buffer);
}

} // namespace webengine
} // namespace mars
