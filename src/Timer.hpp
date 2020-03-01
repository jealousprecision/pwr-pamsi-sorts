#pragma once

#include <iostream>
#include <string>
#include <chrono>

class Timer
{
protected:
    using time_point = std::chrono::time_point<std::chrono::steady_clock>;

public:
    Timer(std::ostream& os_, const std::string& name_) :
        start{std::chrono::steady_clock::now()},
        os{os_},
        name{name_}
    {}

    inline void reset() { start = std::chrono::steady_clock::now(); }

    inline auto checkNow(){ return std::chrono::steady_clock::now() - start; }

    void printNow()
    {
        auto duration = checkNow();
        os << "[" << name << "] printNow(): " << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count()
            << " ms passed" << std::endl;
    }

protected:
    time_point start;
    std::ostream& os;
    std::string name;
};