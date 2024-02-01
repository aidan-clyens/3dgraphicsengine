#pragma once

#include <memory>
#include <chrono>

/*
 * Clock
 */
class Clock {
    public:
        static std::shared_ptr<Clock> instance();

        void init();

        long long get_time_ms();

    private:
        Clock() {}
        Clock(const Clock &) = delete;
        Clock &operator=(const Clock &) = delete;

        std::chrono::system_clock::time_point get_current_time();

        std::chrono::system_clock::time_point m_start_time;
};
