//reishaul1@gmail.com
//first define ascending iterator file
#ifndef ASCENDING_ITERATOR_HPP
#define ASCENDING_ITERATOR_HPP
#include <stdexcept>
#include <iterator>

// This file defines the AscendingIterator class for the MyContainer class.
// The AscendingIterator allows iteration over the elements of MyContainer in ascending order.
namespace Rei{

// Forward declaration of MyContainer class
// This is necessary to allow the AscendingIterator class to access the private members of MyContainer.
template <typename T>
class MyContainer;

template <typename T>//a template class for the AscendingIterator
// Ascending Iterator 
class MyContainer<T>::AscendingIterator {//a nested class of MyContainer
private://objects of this class can only be accessed by MyContainer class
    std::vector<T> sorted;
    size_t index;

public:
    AscendingIterator(const std::vector<T>& original, bool end = false)
        : sorted(original),index(0) {// Constructor that initializes the iterator with the original vector

        std::sort(sorted.begin(), sorted.end());// Sort in ascending order by default
        if(end){index = sorted.size();} // If end is true, set index to the size of the sorted vector, otherwise set it to 0
    }

    /*
    Overloads the * operator to access the current element.
    @return A const reference to the current element.
    @throws std::out_of_range if the iterator is out of range.
    */
    const T& operator*() const {
        if(index>=sorted.size()){throw std::out_of_range("iterator is out of range");}
        return sorted[index];
    }

    // Arrow operator for accessing members of T
    const T* operator->() const {
        if (index >= sorted.size()) {// Check if the index is out of range
            throw std::out_of_range("Iterator is out of range");
        }
        return &sorted[index];
    }

    /*
    Overloads the ++ operator to move to the next element.
    @returns a reference to the current iterator after incrementing it.
    @throws std::out_of_range if the iterator is already at the end of the container.
    */
    AscendingIterator& operator++() {
        if(index >= sorted.size()) {
            throw std::out_of_range("Iterator is out of range");
        }
        if (index < sorted.size()) {
            ++index;
        }
        return *this;
    }
    
    
    /*Overloads the post-increment operator to move to the next element.
    @return a copy of the current iterator before incrementing it.
    @throws std::out_of_range if the iterator is already at the end of the container.
    */
    AscendingIterator operator++(int) {
        if(index >= sorted.size()) {
            throw std::out_of_range("Iterator is out of range");
        }
         // Create a copy of the current iterator
         // and then increment the current iterator
         // to return the old value
        AscendingIterator temp = *this;
        ++(*this);
        return temp;
    }

    // Overloads the -- operator to move to the previous element.
    AscendingIterator& operator--() {
        if (index == 0) {// Check if the index is already at the beginning
            throw std::out_of_range("Cannot decrement iterator before the beginning");
        }
        --index;
        return *this;
    }

    //overloads the != operator to compare two AscendingIterator objects
    //return true if the two iterators are not equal, false otherwise
    bool operator!=(const AscendingIterator& other) const {
        return !(*this == other);
    }
    //overloads the == operator to compare two AscendingIterator objects
    //return true if the two iterators are equal, false otherwise
    bool operator==(const AscendingIterator& other) const {
    return (sorted == other.sorted) && (index == other.index);
    }

};

}
#endif 