#ifndef IVIDEORENDERER_H_YAQ1STO2
#define IVIDEORENDERER_H_YAQ1STO2

#include <array>
#include <boost/optional.hpp>
#include <functional>
#include <memory>

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

/**
 * @brief  A base class for every type capable of producing a video frame: ffmpeg and libVA
 */
struct IVideoRenderer {
    typedef std::function<void()> FrameReadyCb;

    // TODO: Document me
    virtual ~IVideoRenderer() = default;
    virtual boost::optional<VideoFrame> frame() noexcept = 0;
    virtual VideoInfo info() const noexcept = 0;
    virtual void setFrameReadyCb(const FrameReadyCb& cb) noexcept = 0;
};

struct IVideoBackend {
    virtual ~IVideoBackend() = default;

    /**
     * @brief Create a video renderer that will render a specified file
     * @param filename
     * @throw This function will throw an exception if anything bad happens
     *
     * @return
     */
    virtual std::unique_ptr<IVideoRenderer> createVideo(const std::string& filename) const = 0;
};
} // namespace rendering
} // namespace mars

#endif /* end of include guard: IVIDEORENDERER_H_YAQ1STO2 */
