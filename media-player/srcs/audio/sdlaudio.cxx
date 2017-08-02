#include "sdlaudio.h"
#include "log.hpp"

#include <stdexcept>

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <spdlog/fmt/fmt.h>

namespace mars {
namespace audio {

SDLAudio::SDLAudio(const std::string& audio)
{
    current = Mix_LoadMUS(audio.c_str());
    mars_info("SDLAudio(audio={}), current = {}", audio, static_cast<void*>(current));
}

/*static*/ void SDLAudio::initialize()
{
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        mars_error("Unable to initialize audio");
        throw std::runtime_error("Unable to initialize audio");
    }
    int flags = MIX_INIT_MP3 & MIX_INIT_OGG;
    int result = 0;

    if (flags != (result = Mix_Init(flags))) {
        mars_error("Could not initialize mixer (result: {}) error = {}", result, Mix_GetError());
        throw std::runtime_error(
            fmt::format("Could not initialize mixer (result: {}) error = {}", result, Mix_GetError()));
    }
    result = Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);

    mars_info("Opened audio");
}

void SDLAudio::play()
{
    mars_debug("Playing music");
    Mix_PlayMusic(current, 1);
}

void SDLAudio::pause() { Mix_PauseMusic(); }

bool SDLAudio::playing() const { return Mix_PlayingMusic() == 1; }

} // namespace audio
} // namespace mars
