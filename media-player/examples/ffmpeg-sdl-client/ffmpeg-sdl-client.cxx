
#include <SDL2/SDL.h>

#include "ffmpegrenderer.h"

int main(int argc, char* argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {
        printf("Could not initialize SDL - %s\n", SDL_GetError());
        return -1;
    }

    auto screen = SDL_CreateWindow("Simplest ffmpeg player's Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        800, 600, SDL_WINDOW_OPENGL);
    auto sdlRenderer = SDL_CreateRenderer(screen, -1, 0);
    auto sdlTexture = SDL_CreateTexture(sdlRenderer, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING, 480, 272);

    SDL_Rect sdlRect;
    sdlRect.x = 0;
    sdlRect.y = 0;
    sdlRect.w = 480;
    sdlRect.h = 272;

    mars::rendering::FFMPEGRenderer ffmpeg{ std::string{TEST_DIR} + "/bigbuckbunny_480x272.h265" };

    auto frame = ffmpeg.frame();

    while (frame) {
        SDL_UpdateYUVTexture(sdlTexture, &sdlRect, frame->planes[0].pixels, frame->planes[0].linesize,
            frame->planes[1].pixels, frame->planes[1].linesize, frame->planes[2].pixels, frame->planes[2].linesize);
        SDL_RenderClear(sdlRenderer);
        SDL_RenderCopy(sdlRenderer, sdlTexture, nullptr, &sdlRect);
        SDL_RenderPresent(sdlRenderer);
        SDL_Delay(40);
        frame = ffmpeg.frame();
    }
}
