#include "htmlwidget.h"
#include "cefrenderhandler.h"
#include "renderer.h"
#include "itexture.h"
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
    const std::string& url, windowing::Renderer& renderer, std::uint16_t width, std::uint16_t height)
    : Widget(renderer)
    , _renderingTexture(renderer.createTexture(width, height, windowing::PixelFormat::Unknown))
    , _cefRenderer(new mars::webengine::RenderHandler(
          std::bind(&HTMLWidget::updateBuffer, this, std::placeholders::_1), width, height))
    , _browserClient(new mars::webengine::BrowserClient(_cefRenderer))
{
    _width = width;
    _height = height;
    CefWindowInfo window_info;
    CefBrowserSettings browserSettings;
    browserSettings.webgl = STATE_ENABLED;

    window_info.SetAsWindowless(0);
    mars_info_(html, "Creating HTMLWidget with url = {}", url);
    _browser = CefBrowserHost::CreateBrowserSync(window_info, _browserClient.get(), url, browserSettings, nullptr);

    mars_info_(html, "[{}] Created with url = {}, w = {}, h = {}", static_cast<void*>(this), url, _width, _height);
}

HTMLWidget::~HTMLWidget()
{
    mars_info_(html, "[{}] HTMLWidget::~HTMLWidget", static_cast<void*>(this));
    _browser = nullptr;
    _browserClient = nullptr;
    _cefRenderer = nullptr;
}

bool HTMLWidget::update() const noexcept { return true; }
void HTMLWidget::render() noexcept
{
    mars_trace_(html, "HTMLWidget [{}] render()", static_cast<void*>(this));
    _renderingTexture->render(_x, _y);
}
bool HTMLWidget::event(const windowing::EventVariant& event) noexcept
{
    return boost::apply_visitor(html_event_visitor(_browser.get()), event);
}

void HTMLWidget::updateBuffer(const void* buffer)
{
    mars_trace_(html, "[{}] Udating buffer {}, {}", static_cast<void*>(this), _width, _height);
    _renderingTexture->put(buffer, std::make_pair(_width, _height));
    requestRefresh();
}

} // namespace widgets
} // namespace mars
