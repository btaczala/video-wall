#ifndef VIDEOBACKENDMOCK_HPP_RZ8MNCJU
#define VIDEOBACKENDMOCK_HPP_RZ8MNCJU

#include "video/ivideorenderer.h"

struct VideoBackendMock : public mars::rendering::IVideoBackend {
    MAKE_CONST_MOCK1(createVideoProxy, mars::rendering::IVideoRenderer*(const std::string&));

    std::unique_ptr<mars::rendering::IVideoRenderer> createVideo(const std::string& v) const override
    {
        return std::unique_ptr<mars::rendering::IVideoRenderer>(createVideoProxy(v));
    };
};

struct VideoRendererMock : public mars::rendering::IVideoRenderer {
    MAKE_MOCK0(frame, boost::optional<mars::rendering::VideoFrame>(), noexcept, override);
    MAKE_CONST_MOCK0(info, mars::rendering::VideoInfo(), noexcept, override);
};

#endif /* end of include guard: VIDEOBACKENDMOCK_HPP_RZ8MNCJU */
