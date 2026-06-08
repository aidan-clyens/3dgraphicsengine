#include "Timer.h"


/* Timer
 */
Timer::Timer(const std::function<void(void)> &func, unsigned int time_ms):
m_time(std::chrono::milliseconds(time_ms)),
m_func(func),
m_wait_thread([this]() { wait_then_call(); })
{
}

/* ~Timer
 */
Timer::~Timer() {
    m_wait_thread.join();
}

/* wait_then_call
 */
void Timer::wait_then_call() {
    std::this_thread::sleep_for(std::chrono::milliseconds(m_time));
    m_func();
}