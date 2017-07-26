#include "ffmpegrenderer.h"
#include <stdexcept>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
}

namespace mars {
namespace rendering {

    FFMPEGRenderer::FFMPEGRenderer(const std::string& filename)
    {
        av_register_all();

        AVFormatContext* pFormatCtx = NULL;

        if (avformat_open_input(&pFormatCtx, filename.c_str(), nullptr, nullptr) != 0) {
            throw std::runtime_error("");
        }

        if (avformat_find_stream_info(pFormatCtx, nullptr) < 0) {
            throw std::runtime_error("");
        }

        AVCodecContext* pCodecCtxOrig = nullptr;
        AVCodecParameters* pCodecCtx = nullptr;

        // Find the first video stream
        int videoStream = -1;
        for (int i = 0; i < pFormatCtx->nb_streams; i++) {
            if (pFormatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
                videoStream = i;
                break;
            }
        }

        if (videoStream == -1) {
            throw std::runtime_error("");
        }

        // Get a pointer to the codec context for the video stream
        pCodecCtx = pFormatCtx->streams[videoStream]->codecpar;
    }
} // rendering
} // mars
