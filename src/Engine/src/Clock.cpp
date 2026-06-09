#include "Clock.h"

/*
 * instance
 */
std::shared_ptr<Clock> Clock::instance() {
    // Initialize the std::shared_ptr using a custom deleter
    // This is because the Clock has a private constructor that std::make_shared cannot access
    static std::shared_ptr<Clock> instance(nullptr, [](Clock* ptr) {
        delete ptr;
    });

    if (!instance) {
        instance.reset(new Clock());
    }

    return instance;
}

/*
 * init
 */
void Clock::init() {
    m_start_time = this->get_current_time();
}

/*
 * get_time_ms
 */
long long Clock::get_time_ms() {
    return std::chrono::duration_cast<std::chrono::milliseconds>(this->get_current_time() - m_start_time).count();
}

/*
 * get_current_time
 */
std::chrono::system_clock::time_point Clock::get_current_time() {
    return std::chrono::system_clock::now();
}
