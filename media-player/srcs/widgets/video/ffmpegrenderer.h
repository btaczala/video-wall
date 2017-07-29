#ifndef FFMPEGRENDERER_H_HQ7BVLAR
#define FFMPEGRENDERER_H_HQ7BVLAR

#include <atomic>
#include <mutex>
#include <string>
#include <thread>

#include "ivideorenderer.h"

struct AVFormatContext;
struct AVCodecContext;

namespace mars {
namespace rendering {
struct FFMPEGRenderer : public IVideoRenderer {

    /**
     * @brief
     * @param filename
     * @throws
     */
    FFMPEGRenderer(const std::string& filename);

    ~FFMPEGRenderer() override;

    boost::optional<VideoFrame> frame() noexcept override;
    VideoInfo info() const noexcept override;

private:

    boost::optional<VideoFrame> getNextFrame() noexcept;

    const std::string _filepath;
    const std::string _filename;
    AVFormatContext* formatCtx;
    AVCodecContext* codecCtx;
    std::thread _renderingThread;
    std::atomic_bool _keepRendering;
    std::mutex _frameLock;

    boost::optional<VideoFrame> _currentFrame;
};

struct FFMPEGBackend : public IVideoBackend {
    FFMPEGBackend();
    std::unique_ptr<IVideoRenderer> createVideo(const std::string& filename) const override;
};
} // namespace rendering
} // namespace mars

#endif /* end of include guard: FFMPEGRENDERER_H_HQ7BVLAR */
