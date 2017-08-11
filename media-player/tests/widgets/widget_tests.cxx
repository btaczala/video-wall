#include "renderermock.hpp"
#include "widget.h"
#include "widgetmock.hpp"
#include <gtest/gtest.h>
#include <trompeloeil.hpp>

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
    EXPECT_EQ(w.width(), std::numeric_limits<std::uint32_t>::max());
    EXPECT_EQ(w.height(), std::numeric_limits<std::uint32_t>::max());

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

struct WidgetMockWithouthRender : public mars::widgets::Widget {
    WidgetMockWithouthRender()
        : mars::widgets::Widget(_rMock)
    {
    }
    MAKE_CONST_MOCK0(update, bool(), noexcept, override);

    RendererMock _rMock;
};

TEST(Widget, texture_not_set)
{
    WidgetMockWithouthRender widget;
    EXPECT_NO_THROW(widget.render());
}
