#include "renderer.h"
#include "log.hpp"
#include "widget.h"

namespace {
template <typename Callable> struct event_visitor : public boost::static_visitor<void> {
    event_visitor(Callable&& c)
        : _c(c)
    {
    }

    void operator()(mars::windowing::events::Keyboard k) {}

    void operator()(const mars::windowing::events::Quit& ev)
    {
        mars_info_(rendering, "Quit event received, finishing loop");
        _c();
    }
    void operator()(const mars::windowing::events::Refresh& ev) {}

private:
    Callable _c;
};
template <typename Callable> event_visitor<Callable> make_event_visitor(Callable&& c)
{
    return event_visitor<Callable>(std::forward<Callable>(c));
}

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
    mars_info_(rendering, "Start rendering loop");
    bool running = true;
    while (running) {
        auto event = pollEvent();

        if (event) {
            auto vis = make_event_visitor([&running]() { running = false; });
            boost::apply_visitor(vis, event.get());
        }

        for (const auto& f : additionalFunctions) {
            f();
        }
        clear();
        for (const auto& w : _widgets) {
            if (w->update()) {
                w->render();
            }
        }
        render();
    }
    mars_info_(rendering, "Finish rendering loop");
}
}
}
