#ifndef IVIDEORENDERER_H_YAQ1STO2
#define IVIDEORENDERER_H_YAQ1STO2

#include <array>

namespace mars {
namespace rendering {

    struct VideoFrame {
        struct Plane {
            std::uint8_t* pixels;
            int linesize;
        };
        std::array<Plane, 3> planes;
    };

    struct IVideoRenderer {
        virtual ~IVideoRenderer() = default;

        virtual VideoFrame frame() noexcept = 0;
    };
}
}

#endif /* end of include guard: IVIDEORENDERER_H_YAQ1STO2 */
