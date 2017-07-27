#include "ffmpegrenderer.h"
#include "log.hpp"

#include <boost/assert.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/optional.hpp>

#include <spdlog/fmt/fmt.h>
#include <stdexcept>

extern "C" {
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libavutil/imgutils.h>
#include <libswscale/swscale.h>
}

namespace mars {
namespace rendering {

FFMPEGRenderer::FFMPEGRenderer(const std::string& filename)
    : _filename(filename)
    , formatCtx(nullptr)
    , codecCtx(nullptr)
{
    namespace bfs = boost::filesystem;

    if (!bfs::exists(filename)) {
        throw std::runtime_error(fmt::format("file {} does not exists", _filename));
    }

    if (!bfs::is_regular_file(filename)) {
        throw std::runtime_error(fmt::format("file {} is not a file", _filename));
    }

    AVCodec* pCodec{ nullptr };
    av_register_all();

    formatCtx = avformat_alloc_context();

    if (avformat_open_input(&formatCtx, _filename.c_str(), nullptr, nullptr) != 0) {
        mars_warn_(ffmpeg, "Couldn't open input {}", _filename);
        throw std::runtime_error(fmt::format("Couldn't open input {}", _filename));
    }
    if (avformat_find_stream_info(formatCtx, NULL) < 0) {
        mars_warn_(ffmpeg, "Couldn't find stream information");
        throw std::runtime_error("Couldn't find stream information");
    }

    int videoindex = -1;
    for (decltype(formatCtx->nb_streams) i = 0; i < formatCtx->nb_streams; i++)
        if (formatCtx->streams[i]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            videoindex = i;
            break;
        }

    if (videoindex == -1) {
        mars_warn_(ffmpeg, "Didn't find a video stream");
        throw std::runtime_error("Didn't find a video stream");
    }

    codecCtx = formatCtx->streams[videoindex]->codec;
    pCodec = avcodec_find_decoder(codecCtx->codec_id);
    if (!pCodec) {
        mars_warn_(ffmpeg, "Codec not found");
        throw std::runtime_error("Codec not found");
    }
    if (avcodec_open2(codecCtx, pCodec, nullptr) < 0) {
        mars_warn_(ffmpeg, "Could not open codec");
        throw std::runtime_error("Could not open codec");
    }

    av_dump_format(formatCtx, 0, _filename.c_str(), 0);
}

FFMPEGRenderer::~FFMPEGRenderer()
{
    avcodec_close(codecCtx);
    avformat_close_input(&formatCtx);
}

boost::optional<VideoFrame> FFMPEGRenderer::frame() noexcept
{
    BOOST_ASSERT_MSG(formatCtx, "formatCtx must not be nullptr");
    BOOST_ASSERT_MSG(codecCtx, "formatCtx must not be nullptr");

    auto pFrame = av_frame_alloc();
    AVFrame* pFrameYUV = av_frame_alloc();
    unsigned char* out_buffer = reinterpret_cast<unsigned char*>(
        av_malloc(av_image_get_buffer_size(AV_PIX_FMT_YUV420P, codecCtx->width, codecCtx->height, 1)));
    av_image_fill_arrays(
        pFrameYUV->data, pFrameYUV->linesize, out_buffer, AV_PIX_FMT_YUV420P, codecCtx->width, codecCtx->height, 1);
    auto packet = reinterpret_cast<AVPacket*>(av_malloc(sizeof(AVPacket)));
    auto img_convert_ctx = sws_getContext(codecCtx->width, codecCtx->height, codecCtx->pix_fmt, codecCtx->width,
        codecCtx->height, AV_PIX_FMT_YUV420P, SWS_BICUBIC, nullptr, nullptr, nullptr);
    int ret = 0, got_picture = 0;
    int videoIndex = 0;

    if (av_read_frame(formatCtx, packet) >= 0) {
        mars_debug_(ffmpeg, "Getting a frame for {} pos = {}", _filename, packet->pos);
        if (packet->stream_index == videoIndex) {
            ret = avcodec_decode_video2(codecCtx, pFrame, &got_picture, packet);

            if (ret < 0) {
                mars_warn_(ffmpeg, "Unable to decode");
            }

            if (got_picture) {
                sws_scale(img_convert_ctx, (const unsigned char* const*)pFrame->data, pFrame->linesize, 0,
                    codecCtx->height, pFrameYUV->data, pFrameYUV->linesize);
            }
        }
        av_packet_unref(packet);
        av_packet_free(&packet);
        VideoFrame frame;
        frame.planes[0] = { pFrameYUV->data[0], pFrameYUV->linesize[0] };
        frame.planes[1] = { pFrameYUV->data[1], pFrameYUV->linesize[1] };
        frame.planes[2] = { pFrameYUV->data[2], pFrameYUV->linesize[2] };
        av_frame_free(&pFrame);
        av_frame_free(&pFrameYUV);
        av_free(out_buffer);
        sws_freeContext(img_convert_ctx);

        return frame;
    } else {
        mars_warn_(ffmpeg, "There is no frames left in {}", _filename);
    }

    return boost::optional<VideoFrame>{};
}

VideoInfo FFMPEGRenderer::info() const noexcept
{
    return VideoInfo{ static_cast<std::uint16_t>(codecCtx->width), static_cast<std::uint16_t>(codecCtx->height),
        formatCtx->duration };
}

std::unique_ptr<IVideoRenderer> FFMPEGBackend::createVideo(const std::string& filename) const
{
    return std::make_unique<FFMPEGRenderer>(filename);
}
} // rendering
} // mars
