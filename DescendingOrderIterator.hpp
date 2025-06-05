
#pragma once
#include <vector>
#include <algorithm>
#include <functional>
#include <stdexcept>
#include "MyContainer.hpp"

namespace Rei{

template <typename T>

// Descending Iterator 
class MyContainer<T>::DescendingIterator {
private:
    vector<T> sorted;
    size_t index;

public:
    DescendingIterator(const std::vector<T>& original, bool end = false)
        : sorted(original) {
        std::sort(sorted.begin(), sorted.end(), std::greater<T>());
        index = end ? sorted.size() : 0;
    }

    const T& operator*() const {
        if(index>=sorted.size()){throw std:out_of_range("iterator is out of range");}
        return sorted[index];
    }

    DescendingIterator& operator++() {
        ++index;
        return *this;
    }

    bool operator!=(const DescendingIterator& other) const {
        return index != other.index;
    }
};
}

