#pragma once

#include <chrono>
#include <thread>
#include <functional>

/* Timer
 */
class Timer {
    public:
        Timer(const std::function<void(void)> &func, unsigned int time_ms);
        virtual ~Timer();
    
    private:
        void wait_then_call();

        std::chrono::milliseconds m_time;
        std::function <void(void)> m_func;
        std::thread m_wait_thread;
};