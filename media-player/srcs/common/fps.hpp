#ifndef FPS_HPP_FTJEE0XM
#define FPS_HPP_FTJEE0XM

#include "stopwatch.hpp"
#include <cstdint>
#include <thread>

#include "log.hpp"

struct Fps {
    ~Fps()
    {
        running = false;
        if (pingThread.joinable()) {
            pingThread.join();
        }
    }

    void start()
    {
        running = true;
        ticks = 0;
        seconds = 0;
        pingThread = std::thread([this]() {
            while (running) {
                seconds++;
                std::this_thread::sleep_for(std::chrono::seconds(1));

                mars_debug("{} {}", ticks, seconds);
                double fps = static_cast<double>(ticks) / static_cast<double>(seconds);
                mars_debug("Current fps = {}", fps);

                ticks = 0;
                seconds = 0;
            }
        });
        ticks = 0;
    }
    void update() { ticks++; }

private:
    std::int64_t ticks;
    std::int64_t seconds;
    std::thread pingThread;
    bool running;
};

#endif /* end of include guard: FPS_HPP_FTJEE0XM */
