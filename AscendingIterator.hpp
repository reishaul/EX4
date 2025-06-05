#ifndef ASCENDING_ITERATOR_HPP
#define ASCENDING_ITERATOR_HPP

#include "MyContainer.hpp"
#include <vector>
#include <algorithm>
#include <stdexcept>

namespace Rei{

template <typename T>
// Ascending Iterator 
class MyContainer<T>::AscendingIterator {
private:
    vector<T> sorted;
    size_t index;

public:
    AscendingIterator(const vector<T>& original, bool end = false)
        : sorted(original) {
        std::sort(sorted.begin(), sorted.end());// Sort in ascending order by default
        // If end is true, set index to the size of the sorted vector, otherwise set it to 0
        index = end ? sorted.size() : 0;
    }

    const T& operator*() const {
        if(index>=sorted.size()){throw std::out_of_range("iterator is out of range");}
        return sorted[index];
    }

    AscendingIterator& operator++() {
        ++index;
        return *this;
    }

    bool operator!=(const AscendingIterator& other) const {
        return index != other.index;
    }
};

}
#endif 