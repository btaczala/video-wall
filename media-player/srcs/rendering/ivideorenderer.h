#ifndef IVIDEORENDERER_H_YAQ1STO2
#define IVIDEORENDERER_H_YAQ1STO2

#include <array>
#include <boost/optional.hpp>

namespace mars {
namespace rendering {

    struct VideoFrame {
        struct Plane {
            std::uint8_t* pixels;
            int linesize;
        };
        std::array<Plane, 3> planes;
    };

    struct VideoInfo {
        const std::uint16_t width;
        const std::uint16_t height;
        const std::int64_t duration;
    };

    struct IVideoRenderer {
        virtual ~IVideoRenderer() = default;

        virtual boost::optional<VideoFrame> frame() noexcept = 0;

        virtual VideoInfo info() const noexcept = 0;
    };
}
}

#endif /* end of include guard: IVIDEORENDERER_H_YAQ1STO2 */
