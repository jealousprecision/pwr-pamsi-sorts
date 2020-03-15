#pragma once

#include <iostream>
#include <string>
#include <chrono>

class Timer
{
public:
    using time_point = std::chrono::time_point<std::chrono::steady_clock>;

    Timer(std::ostream& os_ = std::cout, const std::string& name_ = "") :
        os{os_},
        name{name_}
    {
        start = std::chrono::steady_clock::now();
    }

    void reset() { start = std::chrono::steady_clock::now(); }
    auto checkNow() const { return std::chrono::steady_clock::now() - start; }
    unsigned checkNowMs() const { return std::chrono::duration_cast<std::chrono::milliseconds>(checkNow()).count(); }
    unsigned checkNowUs() const { return std::chrono::duration_cast<std::chrono::microseconds>(checkNow()).count(); }

protected:
    time_point start;
    std::ostream& os;
    std::string name;
};
