#ifndef CEFBROWSERCLIENT_H_OT7PORY5
#define CEFBROWSERCLIENT_H_OT7PORY5

#include <cef_client.h>

namespace mars {
namespace webengine {

struct BrowserClient : public CefClient, public CefLifeSpanHandler, public CefLoadHandler {
public:
    BrowserClient(CefRefPtr<CefRenderHandler> ptr);
    CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override;
    CefRefPtr<CefLoadHandler> GetLoadHandler() override;
    CefRefPtr<CefRenderHandler> GetRenderHandler() override;

    void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;

    bool DoClose(CefRefPtr<CefBrowser> browser) override;
    void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;

    void OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpStatusCode) override;

    void OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode errorCode,
        const CefString& errorText, const CefString& failedUrl) override;

    void OnLoadingStateChange(
        CefRefPtr<CefBrowser> browser, bool isLoading, bool canGoBack, bool canGoForward) override;

    // void OnLoadStart(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame>
    // frame) override;

    bool closeAllowed() const;
    bool isLoaded() const;

private:
    int browser_id;
    bool closing = false;
    bool loaded = false;
    CefRefPtr<CefRenderHandler> _handler;
    IMPLEMENT_REFCOUNTING(BrowserClient);
};
}
}

#endif /* end of include guard: CEFBROWSERCLIENT_H_OT7PORY5 */
