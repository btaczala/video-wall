#include "cefbrowserclient.h"
#include "log.hpp"

#include <cef_app.h>
#include <cef_client.h>
#include <cef_life_span_handler.h>
#include <cef_load_handler.h>
#include <cef_render_handler.h>
#include <wrapper/cef_helpers.h>

namespace mars {
namespace webengine {
BrowserClient::BrowserClient(const CefRefPtr<CefRenderHandler>& ptr)
    : _handler(ptr)
{
}
CefRefPtr<CefLifeSpanHandler> BrowserClient::GetLifeSpanHandler() { return this; }
CefRefPtr<CefLoadHandler> BrowserClient::GetLoadHandler() { return this; }
CefRefPtr<CefRenderHandler> BrowserClient::GetRenderHandler() { return _handler; }
void BrowserClient::OnAfterCreated(CefRefPtr<CefBrowser> browser)
{
    CEF_REQUIRE_UI_THREAD();
    browser_id = browser->GetIdentifier();
}
void BrowserClient::OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpStatusCode)
{
    mars_debug_(ui, "OnLoadEnd({})", httpStatusCode);
    loaded = true;
}
bool BrowserClient::DoClose(CefRefPtr<CefBrowser> browser)
{
    // Must be executed on the UI thread.
    CEF_REQUIRE_UI_THREAD();

    // Closing the main window requires special handling. See the DoClose()
    // documentation in the CEF header for a detailed description of this
    // process.
    if (browser->GetIdentifier() == browser_id) {
        // Set a flag to indicate that the window close should be allowed.
        closing = true;
    }

    // Allow the close. For windowed browsers this will result in the OS close
    // event being sent.
    return false;
}

void BrowserClient::OnBeforeClose(CefRefPtr<CefBrowser> browser) {}

void BrowserClient::OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode errorCode,
    const CefString& errorText, const CefString& failedUrl)
{
    mars_debug_(ui, "OnLoadError({},{},{},{},{})", static_cast<void*>(browser.get()), static_cast<void*>(frame.get()),
        errorCode, errorText.ToString(), failedUrl.ToString());
}

void BrowserClient::OnLoadingStateChange(
    CefRefPtr<CefBrowser> browser, bool isLoading, bool canGoBack, bool canGoForward)
{
    mars_debug_(
        ui, "OnLoadingStateChange({}, {}, {}, {})", static_cast<void*>(browser), isLoading, canGoBack, canGoForward);
}
bool BrowserClient::closeAllowed() const { return closing; }

bool BrowserClient::isLoaded() const { return loaded; }
} // namespace webengine
} // namespace mars
