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

    inline void reset() { start = std::chrono::steady_clock::now(); }
    inline auto checkNow() const { return std::chrono::steady_clock::now() - start; }
    inline unsigned checkNowMs() const { return std::chrono::duration_cast<std::chrono::milliseconds>(checkNow()).count(); }
    inline unsigned checkNowUs() const { return std::chrono::duration_cast<std::chrono::microseconds>(checkNow()).count(); }
    void printNow(const std::string& msg = "") const
    {
        auto duration = checkNow();
        os << "[" << name << "] printNow(): " << msg << ": " 
            << std::chrono::duration_cast<std::chrono::milliseconds>(duration).count()
            << " ms passed" << std::endl;
    }

protected:
    time_point start;
    std::ostream& os;
    std::string name;
};
