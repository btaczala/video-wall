#include "renderer.h"
#include "log.hpp"
#include "widget.h"

namespace {
using namespace mars::windowing;
struct event_visitor : public boost::static_visitor<void> {
    event_visitor(bool& quitFlag, bool& renderingFlag)
        : _quitFlag(quitFlag)
        , _renderingFlag(renderingFlag)
    {
    }

    void operator()(events::Keyboard) {}
    void operator()(events::Quit) { _quitFlag = true; }
    void operator()(events::Refresh) { _renderingFlag = true; }
    void operator()(events::Window) { _renderingFlag = true; }

    bool& _quitFlag;
    bool& _renderingFlag;
};
} // namespace

namespace mars {
namespace windowing {

void Renderer::addWidget(const std::shared_ptr<widgets::Widget>& w)
{
    mars_info_(rendering, "Adding widget {}", static_cast<void*>(w.get()));
    if (_widgets.empty()) {
        _focused = w;
    }
    _widgets.push_back(w);

    std::sort(
        std::begin(_widgets), std::end(_widgets), [](const auto& sp1, const auto& sp2) { return sp1->z() > sp2->z(); });
}

void Renderer::loop(const std::vector<LoopFn>& additionalFunctions) noexcept
{
    using namespace mars::windowing;
    mars_info_(rendering, "Start rendering loop");
    bool quit = false;
    bool rendering = true;
    while (!quit) {
        auto event = pollEvent();

        if (event) {
            // TODO: Implement a proper lambda visitation here
            auto vis = event_visitor(quit, rendering);
            boost::apply_visitor(vis, event.get());
        }

        for (const auto& f : additionalFunctions) {
            f();
        }

        if (rendering) {
            mars_trace_(rendering, "Trigger rendering");
            clear();
            for (const auto& w : _widgets) {
                if (w->update()) {
                    w->render();
                }
            }
            render();
            rendering = false;
        }
    }
    mars_info_(rendering, "Finish rendering loop");
}
} // namespace windowing
} // namespace mars
