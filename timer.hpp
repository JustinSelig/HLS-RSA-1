#ifndef __TIMER_HPP__
#define __TIMER_HPP__

#include <string>
#include <chrono>

class Timer {
private:
    std::string name;
    std::chrono::high_resolution_clock::time_point begin;
    std::chrono::high_resolution_clock::time_point end;

public:
    Timer(std::string timerName)
        : name(timerName),
          begin(std::chrono::high_resolution_clock::now()),
          end(std::chrono::high_resolution_clock::now())
    {}

    void start(void) {
        begin = std::chrono::high_resolution_clock::now();
    }

    void stop(void) {
        end = std::chrono::high_resolution_clock::now();
    }

    double getDuration(void) {
        return (std::chrono::duration_cast<std::chrono::duration<double>>(end - begin)).count();
    }

};

#endif /* __TIMER_HPP__ */
