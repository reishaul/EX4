//reishaul1@gmail.com
#ifndef REVERSE_ORDER_ITERATOR_HPP
#define REVERSE_ORDER_ITERATOR_HPP

#include "../MyContainer.hpp"
#include <iterator>
#include <stdexcept>


namespace Rei {

template <typename T>
class MyContainer;

template<typename T>

// ReverseOrder Iterator
class MyContainer<T>::ReverseOrderIterator {
private:
    const std::vector<T>& data;
    size_t index;

public:
    // Constructor that initializes the iterator to the end or beginning of the data
    //we start at index data.size and go lower until 0
    ReverseOrderIterator(const std::vector<T>& data,bool end = false)
        : data(data), index(end ? 0 :data.size()) {}


    const T& operator*() const {
        // if (index <= -1) {
        //     throw std::out_of_range("Iterator is out of range");
        // }
        return data[index-1]; // Access the element at the current index
    }

    const T* operator->() const {
        // if (index <= 0) {
        //     throw std::out_of_range("Iterator is out of ");
        // }

        return &data[index-1]; // Access the element at the current index
    }



    ReverseOrderIterator& operator++() {
        if (index == 0) {
            index=data.size();
        }
        else{
            --index;
        }
        return *this;
    }
    ReverseOrderIterator& operator--() {
        if (index >= data.size()) {
            throw std::out_of_range("Cannot decrement iterator before the beginning");
        }
        ++index;
        return *this;
    }

    ReverseOrderIterator operator++(int) {
        if (index == 0) {
            index = data.size();
        } else {
            --index;
        }
        // Create a copy of the current iterator
        // and then increment the current iterator
        ReverseOrderIterator temp = *this;
        ++(*this);
        return temp;
    }


    bool operator==(const ReverseOrderIterator& other) const {
        return (index==other.index)&&(&data==&other.data);
    }
    bool operator!=(const ReverseOrderIterator& other) const {
        return !(*this == other);
    }

};
}
#endif