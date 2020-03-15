#include "PrintTools.hpp"

namespace PrintTools
{

namespace
{

constexpr auto deleteLine = "\033[2K\r";

}  // namespace

void LoadingBar::start()
{
    os_ << text_ << "0\%";
}

void LoadingBar::markProgress(unsigned u)
{
    progress_ += u;
    os_ << deleteLine << text_ << getPercent() << "\%" << std::flush;
}

void LoadingBar::end()
{
    os_ << deleteLine;
}

unsigned LoadingBar::getPercent()
{
    return static_cast<double>(progress_) / max_ * 100;
}

}  // namespace PrintTools
