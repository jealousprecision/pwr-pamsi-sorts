#include "PrintTools.hpp"

#include <memory>

namespace PrintTools
{

namespace
{

constexpr auto deleteLine = "\033[2K\r";

}  // namespace

void LoadingBar::start()
{
    os_ << text_ << "0\%" << std::flush;
}

void LoadingBar::markProgress(unsigned u)
{
    progress_ += u;
    os_ << deleteLine << text_ << getPercent() << "\%" << std::flush;
}

void LoadingBar::end()
{
    os_ << deleteLine << std::flush;
}

unsigned LoadingBar::getPercent()
{
    return static_cast<double>(progress_) / max_ * 100;
}

std::shared_ptr<Sheet<unsigned>> getSheetInstance()
{
    static std::shared_ptr<Sheet<unsigned>> obj(new Sheet<unsigned>());
    return obj;
}

}  // namespace PrintTools
