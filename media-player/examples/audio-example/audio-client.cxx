#include "sdlaudio.h"

#include <SDL2/SDL.h>
#include <iostream>

int main(int argc, char* argv[])
{
    if (argc < 2) {
        return EXIT_FAILURE;
    }

    mars::audio::SDLAudio::initialize();
    mars::audio::SDLAudio player{ argv[1] };

    player.play();

    while (player.playing()) {
    }

    return 0;
}
