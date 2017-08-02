#include "renderer.h"
#include "log.hpp"
#include "widget.h"

#include <boost/hana.hpp>

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
    bool running = true;
    bool rendering = true;
    while (running) {
        auto event = pollEvent();

        if (event) {
            auto visitor = boost::hana::overload([](events::Keyboard k) {},
                [&running](const events::Quit& ev) { running = false; },
                [&rendering](const events::Refresh& ev) { rendering = true; },
                [&rendering](const events::Window& ev) { rendering = true; });
            // clang-format on
            boost::apply_visitor(visitor, event.get());
        }

        for (const auto& f : additionalFunctions) {
            f();
        }

        if (rendering) {
            mars_debug_(rendering, "Trigger rendering");
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
}
}
