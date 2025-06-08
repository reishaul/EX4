//reishaul1@gmail.com
#pragma once
#include "../MyContainer.hpp"//to access MyContainer class
#include <stdexcept>
#include <iterator>

// This file defines the DescendingIterator class for the MyContainer class.
// The DescendingIterator allows iteration over the elements of MyContainer in descending order.
namespace Rei {

// Forward declaration of MyContainer class
// This is necessary to allow the DescendingIterator class to access the private members of MyContainer.
template <typename T>
class MyContainer;

template <typename T>// a template class for the DescendingIterator
// Descending Iterator
class MyContainer<T>::DescendingIterator {// a nested class of MyContainer
private:// objects of this class can only be accessed by MyContainer class
    std::vector<T> sorted;
    size_t index;

public:
    DescendingIterator(const std::vector<T>& original, bool end = false)
        : sorted(original), index(0) {// Constructor that initializes the iterator with the original vector
        std::sort(sorted.begin(), sorted.end(), std::greater<T>());
        if (end) {index = sorted.size();} // If end is true, set index to the size of the sorted vector, otherwise set it to 0
    }

    /*
    Overloads the * operator to access the current element.
    @returns a reference to the current element.
    @throws std::out_of_range if the iterator is out of range.
    */
    const T& operator*() const {
        if (index >= sorted.size()) {
            throw std::out_of_range("Iterator is out of range");
        }
        return sorted[index];// Return a reference to the current element
    }

    /* Overloads the -> operator to access members of T
    @returns a pointer to the current element.
    @throws std::out_of_range if the iterator is out of range.
    */
    const T* operator->() const {
        if (index >= sorted.size()) {
            throw std::out_of_range("Iterator is out of range");
        }
        return &sorted[index];// Return a pointer to the current element
    }

    /*
    Overloads the ++ operator to move to the next element.
    @returns a reference to the current iterator after incrementing it.
    @throws std::out_of_range if the iterator is already at the end of the container.
    */
    DescendingIterator& operator++() {
        if (index >= sorted.size()) {
            throw std::out_of_range("Iterator is out of range");
        }
        ++index;
        return *this;
    }

    /*
    Overloads the -- operator to move to the previous element.
    @returns a reference to the current iterator after decrementing it.
    @throws std::out_of_range if the iterator is already at the beginning of the container.
    */
    DescendingIterator& operator--() {
        if (index == 0) {
            throw std::out_of_range("Cannot decrement iterator before the beginning");
        }
        --index;
        return *this;
    }

    /*
    Overloads the post-increment operator to move to the next element.
    @return a copy of the current iterator before incrementing it.
    @throws std::out_of_range if the iterator is already at the end of the container.
    */
    DescendingIterator operator++(int) {
        if (index >= sorted.size()) {
            throw std::out_of_range("Iterator is out of range");
        }
        DescendingIterator temp = *this;
        ++(*this);
        return temp;
    }

    /*
    Overloads the == operator to compare two DescendingIterator objects.
    @return true if the iterators are equal, false otherwise.
    */
    bool operator==(const DescendingIterator& other) const {
        return (sorted == other.sorted) && (index == other.index);
    }

    /*
    Overloads the != operator to compare two DescendingIterator objects.
    @return true if the two iterators are not equal, false otherwise.
    */
    bool operator!=(const DescendingIterator& other) const {
        return !(*this == other);
    }

};

} 
