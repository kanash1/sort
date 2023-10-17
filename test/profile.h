#pragma once

#ifndef PROFILE_H
#define PROFILE_H

#include <chrono>
#include <iostream>
#include <string>

template<class UnitOfTime = std::chrono::microseconds>
class LogDuration {
public:
    explicit LogDuration(const std::string& msg = "")
        : message(msg + ": ")
        , start(std::chrono::steady_clock::now())
    {
    }

    ~LogDuration() {
        auto finish = std::chrono::steady_clock::now();
        auto dur = finish - start;
        std::cerr << message
            << std::chrono::duration_cast<UnitOfTime>(dur).count() << std::endl;
    }
private:
    std::string message;
    std::chrono::steady_clock::time_point start;
};

#define LOG_UNIQ_ID_IMPL(lineno) _a_local_var_##lineno
#define LOG_UNIQ_ID(lineno) LOG_UNIQ_ID_IMPL(lineno)

#define LOG_DURATION(message, unit_of_time) \
  LogDuration<unit_of_time> LOG_UNIQ_ID(__LINE__){message}

#endif // !PROFILE_H
