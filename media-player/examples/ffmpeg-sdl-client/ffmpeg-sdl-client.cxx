
#include <SDL2/SDL.h>
#include <SDL2pp/SDL2pp.hh>
#include <SDL2pp/Window.hh>

#include <thread>

#include "ffmpegrenderer.h"

int main(int argc, char* argv[])
{
    using namespace SDL2pp;
    try {
        SDL sdl(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

        Window window("libSDL2pp demo", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_OPENGL);
        Renderer renderer(window, -1, SDL_RENDERER_ACCELERATED);

        mars::rendering::FFMPEGRenderer ffmpeg{ std::string{ TEST_DIR } + "/bigbuckbunny_480x272.h265" };
        auto info = ffmpeg.info();
        Texture videoTexture(renderer, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING, info.width, info.height);

        auto frame = ffmpeg.frame();

        while (frame) {
            videoTexture.UpdateYUV(Rect(0, 0, info.width, info.height), frame->planes[0].pixels,
                frame->planes[0].linesize, frame->planes[1].pixels, frame->planes[1].linesize, frame->planes[2].pixels,
                frame->planes[2].linesize);

            renderer.Clear();
            renderer.Copy(videoTexture, Rect(0,0,480, 272), Rect(0, 0, 480, 272));
            renderer.Copy(videoTexture, Rect(0,0,480, 272), Rect(500, 0, 480, 272));
            //renderer.Copy(videoTexture, Rect(0,0,480/2, 272/2), Rect(0, 0, 480, 272));
            renderer.Present();
            std::this_thread::sleep_for(std::chrono::milliseconds(40));
            frame = ffmpeg.frame();
        }
    } catch (const std::exception& ex) {
    }
}
