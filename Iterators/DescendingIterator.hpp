//reishaul1@gmail.com
#pragma once
#include "../MyContainer.hpp"
#include <stdexcept>
#include <iterator>

namespace Rei {

template <typename T>
class MyContainer;

template <typename T>
class MyContainer<T>::DescendingIterator {
private:
    std::vector<T> sorted;
    size_t index;

public:
    DescendingIterator(const std::vector<T>& original, bool end = false)
        : sorted(original), index(0) {
        std::sort(sorted.begin(), sorted.end(), std::greater<T>());
        if (end) {
            index = sorted.size();
        }
    }

    const T& operator*() const {
        if (index >= sorted.size()) {
            throw std::out_of_range("Iterator is out of range");
        }
        return sorted[index];
    }

    const T* operator->() const {
        if (index >= sorted.size()) {
            throw std::out_of_range("Iterator is out of range");
        }
        return &sorted[index];
    }

    DescendingIterator& operator++() {
        if (index >= sorted.size()) {
            throw std::out_of_range("Iterator is out of range");
        }
        ++index;
        return *this;
    }

    DescendingIterator& operator--() {
        if (index == 0) {
            throw std::out_of_range("Cannot decrement iterator before the beginning");
        }
        --index;
        return *this;
    }

    DescendingIterator operator++(int) {
        if (index >= sorted.size()) {
            throw std::out_of_range("Iterator is out of range");
        }
        DescendingIterator temp = *this;
        ++(*this);
        return temp;
    }

    bool operator==(const DescendingIterator& other) const {
        return (sorted == other.sorted) && (index == other.index);
    }

    bool operator!=(const DescendingIterator& other) const {
        return !(*this == other);
    }

};

} 
