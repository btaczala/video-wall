#include "ffmpegrenderer.h"

#include <stdexcept>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}

namespace mars {
namespace rendering {

FFMPEGRenderer::FFMPEGRenderer(const std::string& filename) {
    av_register_all();

    AVFormatContext* pFormatCtx = NULL;

    if (avformat_open_input(&pFormatCtx, filename.c_str(), nullptr, nullptr) !=
        0) {
        throw std::runtime_error("");
    }
}
}
}
