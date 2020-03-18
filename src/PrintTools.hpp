#pragma once

#include <iostream>
#include <iomanip>
#include <memory>
#include <string>
#include <sstream>
#include <vector>

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

template<typename T>
class Sheet : public std::enable_shared_from_this<Sheet<T>>
{
public:
    class Row
    {
    public:
        using value_type = T;

        Row() = delete;
        Row(std::shared_ptr<Sheet> parent, size_t idx) :
            parent_(parent), idx_(idx)
        {}

        void setName(const std::string& newName)
        {
            parent_->data_[idx_].name = newName;
        }

        std::vector<T>& operator*() { return parent_->data_[idx_].data; }
        std::vector<T>* operator->() { return &(parent_->data_[idx_].data); }

    protected:
        std::shared_ptr<Sheet<T>> parent_;
        size_t idx_;
    };

    Sheet() = default;

    Sheet& operator+= (const Sheet& other)
    {
        std::copy(other.data_.begin(), other.data_.end(), std::back_inserter(data_));
        return *this;
    }

    Row newRow()
    {
        data_.push_back(InternalRow());
        return Row(this->shared_from_this(), data_.size() - 1);
    }

    void dump(std::ostream& os)
    {
        for (auto& row : data_)
            os << row.name << ",";

        os << std::endl;

        for (int y = 0; y < data_[0].data.size(); ++y)
        {
            for (int x = 0; x < data_.size(); ++x)
                if (y < data_[x].data.size())
                    os << data_[x].data[y] << ",";
                else
                    os << ",";

            os << std::endl;
        }
    }

protected:
    struct InternalRow
    {
        std::string name = "";
        std::vector<T> data;
    };

    std::vector<InternalRow> data_;
};

std::shared_ptr<Sheet<unsigned>> getSheetInstance();

template<typename T>
std::string to_string_with_precision(T t, size_t precision = 6)
{
    if (precision == 0)
    {
        size_t cnt = 0;
        auto temp = t;

        while (temp > 1)
        {
            temp /= 10;
            cnt++;
        }

        precision = cnt;
    }

    std::stringstream sst;
    sst << std::setprecision(precision) << t;
    return sst.str();
}

}  // namespace PrintTools
