#ifndef RATE_TRACKER_H
#define RATE_TRACKER_H

#include <AP_HAL/AP_HAL.h>
#include <cstdint>
#include <array>

class RateTracker {
public:
    RateTracker();
    void addEvent();
    int8_t getRate();

private:
    static const int32_t WINDOW_SIZE = 5; // 5 seconds window
    static const int32_t BUFFER_SIZE = WINDOW_SIZE + 1; // +1 to differentiate between full and empty

    std::array<int32_t, BUFFER_SIZE> event_counts;
    int32_t head;
    int32_t tail;
    int32_t total_events;
    int32_t last_update_time;
    int32_t rate;

    int32_t getCurrentTime();
    void updateBuffer(int32_t current_time);
    void updateRate();
};

#endif // RATE_TRACKER_H