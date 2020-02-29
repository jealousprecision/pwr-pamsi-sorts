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

}  // namespace PrintTools
