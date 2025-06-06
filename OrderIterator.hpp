//reishaul1@gmail.com
#ifndef ORDER_ITERATOR_HPP
#define ORDER_ITERATOR_HPP

#include "MyContainer.hpp"
#include <iterator>
#include <stdexcept>

namespace Rei{

template <typename T>
class MyContainer;


template<typename T>

// Order Iterator
class MyContainer<T>::OrderIterator {
private:
    const std::vector<T>& data;
    size_t index;

public:
    // Constructor that initializes the iterator to the end or beginning of the data
    OrderIterator(const std::vector<T>& data, bool end = false)
        : data(data), index(end ? data.size() : 0) {}

    const T& operator*() const {
        return data[index];// Access the element at the current index
    }

    const T* operator->() const{
        return &data[index];
    } 


    OrderIterator& operator++() {
        index++;
        return *this;
    }

    OrderIterator operator++(int) {
        OrderIterator temp = *this;
        ++(*this);
        return temp;
    }

    bool operator==(const OrderIterator& other)const{
        return (index==other.index)&&(&data==&other.data);
    }

    bool operator!=(const OrderIterator& other) const {
        return !(*this==other);
    }

};

}
#endif
