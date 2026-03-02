    #pragma once
#include <chrono>

class Timer {
public:
    Timer() : start_(std::chrono::high_resolution_clock::now()) {}

    double elapsed_ms() const {
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> diff = end - start_;
        return diff.count();
    }

private:
    std::chrono::high_resolution_clock::time_point start_;
};