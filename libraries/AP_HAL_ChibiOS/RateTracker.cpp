#include "RateTracker.h"

RateTracker::RateTracker() : head(0), tail(0), total_events(0), last_update_time(getCurrentTime()), rate(0) {
    event_counts.fill(0);
}

void RateTracker::addEvent() {
    int32_t current_time = getCurrentTime();
    updateBuffer(current_time);
    event_counts[head]++;
    total_events++;
    updateRate();
}

int8_t RateTracker::getRate() {
    int32_t current_time = getCurrentTime();
    updateBuffer(current_time);
    updateRate();
    return rate;
}

int32_t RateTracker::getCurrentTime() {
    return static_cast<int32_t>(AP_HAL::micros() / 1000000); // Convert microseconds to seconds
}

void RateTracker::updateBuffer(int32_t current_time) {
    int32_t time_diff = current_time - last_update_time;
    if (time_diff == 0) return;

    for (int32_t i = 0; i < time_diff; i++) {
        head = (head + 1) % BUFFER_SIZE;
        if (head == tail) {
            total_events -= event_counts[tail];
            tail = (tail + 1) % BUFFER_SIZE;
        }
        event_counts[head] = 0;
    }

    last_update_time = current_time;
}

void RateTracker::updateRate() {
    rate = total_events / WINDOW_SIZE;
}