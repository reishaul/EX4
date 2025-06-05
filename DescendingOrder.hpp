//reishaul1@gmail.com
#ifndef DESCENDINGORDER_HPP
#define DESCENDINGORDER_HPP
#include <vector>
#include <algorithm>F


using std::vector;
namespace Rei {


    class DescendingOrder {
    private:
        std::vector<T> data;  
        size_t size_;

    public:
        DescendingOrder(const vector<T>& input) : data(input), index(0), size_(input.size()) {
            std::sort(data.begin(), data.end(), std::greater<T>());
        }
        T operator*()const{return data[index];}

        DescendingOrder& operator++() {
            if (index < size_) {
                ++index;
            }
            return *this;
        }
        bool operator!=(const DescendingOrder& other) const {
            return index != other.index;
        }

        bool operator==(const DescendingOrder& other) const {
            return index == other.index;
        }

        static DescendingOrder begin(const vector<T>& input) {
            return DescendingOrder(input);
        }

        static DescendingOrder end(const MyContainer<T>& a) {

            DescendingOrder temp(a.data);
            temp.index = temp.data.size();
            return temp;
        }


        DescendingOrder beginDescending() const {
            return DescendingOrder::begin(*this);
        }

        DescendingOrder endDescending() const {
            return DescendingOrder::end(*this);
        }
    };
}