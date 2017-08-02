#ifndef SDLAUDIO_H_GOSF6QPW
#define SDLAUDIO_H_GOSF6QPW

#include <string>
struct _Mix_Music;

namespace mars {
namespace audio {
struct SDLAudio {
    SDLAudio(const std::string& file);

    void play();
    void pause();

    bool playing() const;

    static void initialize();

private:
    _Mix_Music* current{ nullptr };
};
} // namespace audio
} // namespace mars

#endif /* end of include guard: SDLAUDIO_H_GOSF6QPW */
