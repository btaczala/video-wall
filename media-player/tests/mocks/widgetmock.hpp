#ifndef WIDGETMOCK_HPP_4YKLUW1Q
#define WIDGETMOCK_HPP_4YKLUW1Q

#include "widget.h"

struct WidgetMock : public mars::widgets::Widget {
    WidgetMock()
        : mars::widgets::Widget(_rMock)
    {
    }
    MAKE_CONST_MOCK0(update, bool(), noexcept, override);
    MAKE_MOCK0(render, void(), noexcept, override);

    void rr() { requestRefresh(); }

    RendererMock _rMock;
};

#endif /* end of include guard: WIDGETMOCK_HPP_4YKLUW1Q */
