#include <gtest/gtest.h>
#include <trompeloeil.hpp>

#include "renderermock.hpp"
#include "video/videowidget.h"
#include "videobackendmock.hpp"

namespace boost {
std::ostream& operator<<(std::ostream& os, const mars::rendering::VideoFrame&) { return os; }
}

#include <boost/optional/optional_io.hpp>

struct VideoWidgetTests : public ::testing::Test {

    RendererMock _mock;
    VideoBackendMock _videoBackendMock;
};

TEST_F(VideoWidgetTests, create_video_widget)
{
    using namespace mars::rendering;
    using namespace mars::windowing;
    auto video = new VideoRendererMock;

    VideoInfo vi{ 10, 10, 15 };

    REQUIRE_CALL(_videoBackendMock, createVideoProxy(trompeloeil::_)).RETURN(video);
    REQUIRE_CALL(*video, info()).RETURN(vi).TIMES(AT_LEAST(1));
    REQUIRE_CALL(*video, setFrameReadyCb(trompeloeil::_));

    ITexture* texture = nullptr;
    REQUIRE_CALL(_mock, createTextureProxy(vi.width, vi.height, mars::windowing::PixelFormat::IYUV)).RETURN(texture);

    auto fn = [this]() { mars::widgets::VideoWidget vw{ "", _mock, _videoBackendMock }; };
    EXPECT_NO_THROW(fn());
}

struct VideoWidgetCreatedTests : public ::testing::Test {

    void SetUp() override
    {
        using namespace mars::rendering;
        using namespace mars::windowing;
        video = new VideoRendererMock;

        VideoInfo vi{ 10, 10, 15 };

        REQUIRE_CALL(_videoBackendMock, createVideoProxy("")).RETURN(video);
        REQUIRE_CALL(*video, info()).RETURN(vi).TIMES(AT_LEAST(1));
        REQUIRE_CALL(*video, setFrameReadyCb(trompeloeil::_));

        _texture = new TextureMock;
        REQUIRE_CALL(_mock, createTextureProxy(vi.width, vi.height, mars::windowing::PixelFormat::IYUV))
            .RETURN(_texture);
        vw = std::make_unique<mars::widgets::VideoWidget>("", _mock, _videoBackendMock);
    }

    RendererMock _mock;
    VideoBackendMock _videoBackendMock;
    VideoRendererMock* video;
    std::unique_ptr<mars::widgets::VideoWidget> vw;
    TextureMock* _texture;
};

TEST_F(VideoWidgetCreatedTests, update_frames_left)
{
    using namespace mars::rendering;
    using namespace mars::windowing;
    using trompeloeil::_;
    VideoFrame f{
        { { VideoFrame::Plane{ nullptr, -1 }, VideoFrame::Plane{ nullptr, 0 }, VideoFrame::Plane{ nullptr, 0 } } }
    };
    VideoInfo vi{ 10, 10, 15 };
    boost::optional<VideoFrame> ff{ f };
    REQUIRE_CALL(*video, info()).RETURN(vi).TIMES(AT_LEAST(1));
    REQUIRE_CALL(*video, frame()).RETURN(ff);
    REQUIRE_CALL(*_texture, UpdateYUVTexture(_, _, _, _, _, _, _));

    EXPECT_TRUE(vw->update());

    EXPECT_EQ(vw->x(), 0u);
    EXPECT_EQ(vw->y(), 0u);
    EXPECT_EQ(vw->width(), 10u);
    EXPECT_EQ(vw->height(), 10u);
}

TEST_F(VideoWidgetCreatedTests, handle_event)
{
    mars::windowing::EventVariant event;
    event = mars::windowing::events::Keyboard{};
    EXPECT_TRUE(vw->event(event));

    event = mars::windowing::events::Quit{};
    EXPECT_FALSE(vw->event(event));
}
