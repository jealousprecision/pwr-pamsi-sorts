#pragma once

#include <iostream>
#include <string>

namespace PrintTools
{

template<typename Iter>
struct IterPrinter
{
    Iter first;
    Iter end;
};

template<typename Iter>
std::ostream& operator<<(std::ostream& os, const IterPrinter<Iter>& printer)
{
    for (auto it = printer.first; it != printer.end; ++it)
        os << *it << ", ";
    return os;
}

template<typename Cont>
struct ContPrinter
{
    const Cont& cont;
};

template<typename Cont>
std::ostream& operator<<(std::ostream& os, const ContPrinter<Cont>& printer)
{
    for (const auto& el : printer.cont)
        os << el << ", ";
    return os;
}

template<typename Iter>
IterPrinter<Iter> prettyPrint(Iter first, Iter end)
{
    return IterPrinter<Iter>{first, end};
}

template<typename Cont>
ContPrinter<Cont> prettyPrint(const Cont& cont)
{
    return ContPrinter<Cont>{cont};
}

class LoadingBar
{
public:
    LoadingBar(std::ostream& os, std::string text, unsigned max) :
        os_(os), text_(text), max_(max)
    {}

    void start();
    void markProgress(unsigned);
    void end();

private:
    unsigned getPercent();

    std::ostream& os_;
    std::string text_;
    unsigned max_;
    unsigned progress_ = 0;
};

}  // namespace PrintTools
