#ifndef HTMLWIDGET_H_AWUUR1O6
#define HTMLWIDGET_H_AWUUR1O6

#include "cefbrowserclient.h"
#include "cefrenderhandler.h"
#include "widget.h"

#include <cef_browser.h>

namespace mars {
namespace windowing {
struct Renderer;
struct ITexture;
} // namespace rendering

namespace widgets {

struct HTMLWidget : public Widget {

    HTMLWidget(const std::string& url, windowing::Renderer& renderer, std::uint16_t width, std::uint16_t height);
    ~HTMLWidget();

    bool update() const noexcept override;

    void render() noexcept override;

    bool event(const windowing::EventVariant& event) noexcept override;

private:
    void updateBuffer(const void* buffer);

    const std::unique_ptr<windowing::ITexture> _renderingTexture;

    CefRefPtr<mars::webengine::RenderHandler> _cefRenderer;
    CefRefPtr<mars::webengine::BrowserClient> _browserClient;
    CefRefPtr<CefBrowser> _browser;
};
} // widgets
} // mars

#endif /* end of include guard: HTMLWIDGET_H_AWUUR1O6 */
