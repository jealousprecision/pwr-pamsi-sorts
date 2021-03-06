#include "PrintTools.hpp"

#include <memory>

namespace PrintTools
{

const char* deleteLine = "\033[2K\r";

void LoadingBar::start()
{
    os_ << text_ << "0%" << std::flush;
}

void LoadingBar::markProgress(unsigned u)
{
    progress_ += u;
    os_ << deleteLine << text_ << getPercent() << "%" << std::flush;
}

void LoadingBar::end()
{
    os_ << deleteLine << std::flush;
}

unsigned LoadingBar::getPercent()
{
    return static_cast<double>(progress_) / max_ * 100;
}

}  // namespace PrintTools
