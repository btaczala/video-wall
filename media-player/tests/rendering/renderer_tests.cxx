#include <gtest/gtest.h>
#include <trompeloeil.hpp>

#include <boost/optional/optional_io.hpp>

#include "renderermock.hpp"
#include "widget.h"
#include "widgetmock.hpp"

struct RendererTests : public ::testing::Test {
    RendererMock renderer;
};

TEST_F(RendererTests, loop_immidiately_quit)
{
    using namespace mars::windowing;
    EventVariant ev{ events::Quit{} };
    REQUIRE_CALL(renderer, pollEventProxy()).LR_RETURN(&ev);
    REQUIRE_CALL(renderer, clear());
    REQUIRE_CALL(renderer, render());
    renderer.loop();
}

TEST_F(RendererTests, loop_refresh)
{
    using namespace mars::windowing;
    trompeloeil::sequence seq;
    EventVariant ev{ events::Refresh{} };
    EventVariant quit{ events::Quit{} };
    REQUIRE_CALL(renderer, pollEventProxy()).LR_RETURN(&ev).TIMES(4).IN_SEQUENCE(seq);
    REQUIRE_CALL(renderer, pollEventProxy()).LR_RETURN(&quit).TIMES(1).IN_SEQUENCE(seq);
    REQUIRE_CALL(renderer, clear()).TIMES(4);
    REQUIRE_CALL(renderer, render()).TIMES(4);
    renderer.loop();
}

TEST_F(RendererTests, loop_with_null_widget)
{
    using namespace mars::windowing;
    trompeloeil::sequence seq;

    renderer.addWidget(nullptr);

    EventVariant ev{ events::Refresh{} };
    EventVariant quit{ events::Quit{} };
    REQUIRE_CALL(renderer, pollEventProxy()).LR_RETURN(&ev).TIMES(1).IN_SEQUENCE(seq);
    REQUIRE_CALL(renderer, pollEventProxy()).LR_RETURN(&quit).TIMES(1).IN_SEQUENCE(seq);
    ALLOW_CALL(renderer, clear());
    ALLOW_CALL(renderer, render());
    renderer.loop();
}

TEST_F(RendererTests, loop_with_widget)
{
    using namespace mars::windowing;
    trompeloeil::sequence seq;

    auto pw = std::make_shared<WidgetMock>();
    renderer.addWidget(pw);

    EventVariant ev{ events::Refresh{} };
    EventVariant quit{ events::Quit{} };
    REQUIRE_CALL(renderer, pollEventProxy()).LR_RETURN(&ev).TIMES(1).IN_SEQUENCE(seq);
    REQUIRE_CALL(renderer, pollEventProxy()).LR_RETURN(&quit).TIMES(1).IN_SEQUENCE(seq);
    ALLOW_CALL(renderer, clear());
    ALLOW_CALL(renderer, render());

    REQUIRE_CALL(*pw, update()).RETURN(true).TIMES(1);
    REQUIRE_CALL(*pw, render()).TIMES(1);

    renderer.loop();
}
