#ifndef FFMPEGRENDERER_H_HQ7BVLAR
#define FFMPEGRENDERER_H_HQ7BVLAR

#include <string>

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

    ~FFMPEGRenderer();

    virtual boost::optional<VideoFrame> frame() noexcept override;
    virtual VideoInfo info() const noexcept override;

private:
    const std::string _filepath;
    const std::string _filename;
    AVFormatContext* formatCtx;
    AVCodecContext* codecCtx;
};

struct FFMPEGBackend : public IVideoBackend {
    FFMPEGBackend();
    virtual std::unique_ptr<IVideoRenderer> createVideo(const std::string& filename) const override;
};
}
}

#endif /* end of include guard: FFMPEGRENDERER_H_HQ7BVLAR */
