#ifndef REVERSE_ORDER_ITERATOR_HPP
#define REVERSE_ORDER_ITERATOR_HPP

#include "MyContainer.hpp"


namespace Rei{
template <typename T>
class MyContainer;



template<typename T>

// ReverseOrder Iterator
class MyContainer<T>::ReverseOrderIterator {
private:
    const vector<T>& data;
    size_t index;

public:
    // Constructor that initializes the iterator to the end or beginning of the data
    ReverseOrderIterator(const vector<T>& data, bool end = false)
        : data(data), index(end ? data.size() : 0) {}

    const T& operator*() const {
        return data[index-1];// Access the element at the current index
    }

    ReverseOrderIterator& operator++() {
        index--;
        return *this;
    }

    bool operator!=(const ReverseOrderIterator& other) const {
        return index != other.index;
    }
};
}
#endif