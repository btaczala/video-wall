#include "renderer.h"
#include "lambda_visitor.hpp"
#include "log.hpp"
#include "texture.h"
#include "widget.h"

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

void Renderer::setFocus(const std::shared_ptr<widgets::Widget>& w) { _focused = w; }

void Renderer::loop(const std::vector<LoopFn>& additionalFunctions) noexcept
{
    using namespace mars::windowing;
    mars_info_(rendering, "Start rendering loop");
    bool quit = false;
    bool rendering = true;
    while (!quit) {
        auto event = pollEvent();

        if (event) {
            auto lambda_visitor = make_lambda_visitor<void>(
                [this](const events::Keyboard& k) {
                    if (_focused) {
                        _focused->event(k);
                    }
                },
                [&quit](const events::Quit& q) { quit = true; },
                [&rendering](const events::Refresh& q) { rendering = true; },
                [&rendering](const events::Window& q) { rendering = true; });
            boost::apply_visitor(lambda_visitor, event.get());
        }

        for (const auto& f : additionalFunctions) {
            f();
        }

        if (rendering) {
            mars_trace_(rendering, "Trigger rendering");
            clear();
            for (const auto& w : _widgets) {
                if (w && w->update()) {
                    w->render();
                }
            }
            render();
            rendering = false;
        }
    }

    rendering = false;

    mars_info_(rendering, "Finish rendering loop");
}

} // namespace windowing
} // namespace mars
