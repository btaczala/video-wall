#include "htmlwidget.h"
#include "cefrenderhandler.h"
#include "log.hpp"

namespace {
struct html_event_visitor : public boost::static_visitor<bool> {

    html_event_visitor(CefBrowser* browser)
        : _browser(browser)
    {
    }

    template <typename T>
    bool operator()(
        T&& t, typename std::enable_if<!std::is_same<T, mars::windowing::events::Quit>::value>::type* = nullptr) const
    {
        return false;
    }

    bool operator()(const mars::windowing::events::Quit& t) const
    {
        _browser->GetHost()->CloseBrowser(false);
        return true;
    }

private:
    CefBrowser* _browser;
};
} // namespace

namespace mars {
namespace widgets {

HTMLWidget::HTMLWidget(
    const std::string& url, windowing::IRenderer& renderer, std::uint16_t width, std::uint16_t height)
    : _cefRenderer(new mars::webengine::RenderHandler(&renderer, width, height))
    , _browserClient(new mars::webengine::BrowserClient(_cefRenderer))
{
    CefWindowInfo window_info;
    CefBrowserSettings browserSettings;
    browserSettings.webgl = STATE_ENABLED;

    window_info.SetAsWindowless(0);
    mars_info_(html, "Creating HTMLWidget with url = {}", url);
    _browser = CefBrowserHost::CreateBrowserSync(window_info, _browserClient.get(), url, browserSettings, nullptr);
}

HTMLWidget::~HTMLWidget()
{
    mars_info_(html, "HTMLWidget::~HTMLWidget");
    _browser = nullptr;
    _browserClient = nullptr;
    _cefRenderer = nullptr;
}

bool HTMLWidget::update() noexcept { return true; }
void HTMLWidget::render() noexcept { _cefRenderer->render(); }
bool HTMLWidget::event(const windowing::EventVariant& event) noexcept
{
    return boost::apply_visitor(html_event_visitor(_browser.get()), event);
    return false;
}

} // widgets
} // mars
