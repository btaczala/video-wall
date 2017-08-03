#include "renderermock.hpp"
#include "widget.h"
#include <gtest/gtest.h>
#include <trompeloeil.hpp>

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

TEST(Widget, event_return_false)
{
    WidgetMock w;
    EXPECT_FALSE(w.event(mars::windowing::EventVariant{}));
}

TEST(Widget, default_position)
{
    WidgetMock w;
    EXPECT_EQ(w.x(), 0u);
    EXPECT_EQ(w.y(), 0u);
    EXPECT_EQ(w.width(), 0u);
    EXPECT_EQ(w.height(), 0u);

    w.move(10, 10);
    EXPECT_EQ(w.x(), 10u);
    EXPECT_EQ(w.y(), 10u);
}

TEST(Widget, request_refresh)
{
    WidgetMock w;
    REQUIRE_CALL(w._rMock, requestRefresh(::trompeloeil::_));

    w.rr();
}
