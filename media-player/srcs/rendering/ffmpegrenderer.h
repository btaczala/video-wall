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

        virtual VideoFrame frame() noexcept override;

    private:

        const std::string _filename;
        AVFormatContext* formatCtx;
        AVCodecContext* codecCtx;
    };
}
}

#endif /* end of include guard: FFMPEGRENDERER_H_HQ7BVLAR */
