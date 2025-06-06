//reishaul1@gmail.com
#ifndef ASCENDING_ITERATOR_HPP
#define ASCENDING_ITERATOR_HPP

#include <stdexcept>
#include <iterator>


namespace Rei{

template <typename T>
class MyContainer;

template <typename T>
// Ascending Iterator 
class MyContainer<T>::AscendingIterator {
private:
    std::vector<T> sorted;
    size_t index;

public:
    AscendingIterator(const std::vector<T>& original, bool end = false)
        : sorted(original),index(0) {

        std::sort(sorted.begin(), sorted.end());// Sort in ascending order by default
        if(end){index = sorted.size();} // If end is true, set index to the size of the sorted vector
        // If end is true, set index to the size of the sorted vector, otherwise set it to 0
        
    }

    const T& operator*() const {
        if(index>=sorted.size()){throw std::out_of_range("iterator is out of range");}
        return sorted[index];
    }

    // Arrow operator for accessing members of T
    const T* operator->() const {
        if (index >= sorted.size()) {
            throw std::out_of_range("Iterator is out of range");
        }
        return &sorted[index];
    }


    AscendingIterator& operator++() {
        if (index < sorted.size()) {
            ++index;
        }
        return *this;
    }

    AscendingIterator operator++(int) {
        AscendingIterator temp = *this;
        ++(*this);
        return temp;
    }

    bool operator!=(const AscendingIterator& other) const {
        return !(*this == other);
    }

    bool operator==(const AscendingIterator& other) const {
    return (sorted == other.sorted) && (index == other.index);
    }


    // // Iterator traits (for compatibility with STL algorithms)
    // using iterator_category = std::forward_iterator_tag;
    // using value_type = T;
    // using difference_type = std::ptrdiff_t;
    // using pointer = const T*;
    // using reference = const T&;
};

}
#endif 