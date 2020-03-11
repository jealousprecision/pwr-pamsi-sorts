#pragma once

#include <iostream>
#include <string>

namespace PrintTools
{

template<typename Container>
void printContainer(
    std::ostream& os,
    const Container& container,
    const std::string& deli,
    const std::string& end)
{
    for (decltype(auto) el : container)
        os << el << deli;

    os << end;
}

template<typename Container>
void printContainer(
    std::ostream& os,
    const Container& container)
{
    printContainer(os, container, ", ", "");
}

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
    ContPrinter(const Cont& cont) :
        cont_(cont)
    {}

    ContPrinter(const ContPrinter&) = default;

    const Cont& cont_;
};

template<typename Cont>
std::ostream& operator<<(std::ostream& os, const ContPrinter<Cont>& printer)
{
    for (const auto& el : printer.cont_)
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
    return ContPrinter<Cont>(cont);
}

}  // namespace PrintTools
