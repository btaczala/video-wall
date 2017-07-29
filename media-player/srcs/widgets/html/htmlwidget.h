#ifndef HTMLWIDGET_H_AWUUR1O6
#define HTMLWIDGET_H_AWUUR1O6

#include "iwidget.h"
#include "cefrenderhandler.h"
#include "cefbrowserclient.h"

#include <cef_browser.h>

namespace mars {
namespace windowing {
struct IRenderer;
} // namespace rendering

namespace widgets {

struct HTMLWidget : public IWidget {

    HTMLWidget(const std::string& url, windowing::IRenderer& renderer, std::uint16_t width, std::uint16_t height);
    ~HTMLWidget();

    bool update() noexcept override;

    void render() noexcept override;

    void moveTo(std::uint16_t newX, std::uint16_t newY) override;

    bool event(const windowing::EventVariant& event) noexcept override;

private:
    CefRefPtr<mars::webengine::RenderHandler> _cefRenderer;
    CefRefPtr<mars::webengine::BrowserClient> _browserClient;
    CefRefPtr<CefBrowser> browser;
};
} // widgets
} // mars

#endif /* end of include guard: HTMLWIDGET_H_AWUUR1O6 */
