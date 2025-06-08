//reishaul1@gmail.com
#ifndef REVERSE_ORDER_ITERATOR_HPP
#define REVERSE_ORDER_ITERATOR_HPP

#include "../MyContainer.hpp"// Include the MyContainer header to access the container's data
#include <iterator>
#include <stdexcept>

// This file defines the ReverseOrderIterator class for the MyContainer class.
// The ReverseOrderIterator allows iteration over the elements of MyContainer in reverse order.
namespace Rei {

// Forward declaration of MyContainer class
// This is necessary to allow the ReverseOrderIterator class to access the private members of MyContainer.
template <typename T>
class MyContainer;

template<typename T>// A template class for the ReverseOrderIterator

// ReverseOrder Iterator
class MyContainer<T>::ReverseOrderIterator {// A nested class of MyContainer
private://objects of this class can only be accessed by MyContainer class
    const std::vector<T>& data;
    size_t index;

public:
    // Constructor that initializes the iterator to the end or beginning of the data
    //we start at index data.size and go lower until 0
    ReverseOrderIterator(const std::vector<T>& data,bool end = false)
        : data(data), index(end ? 0 :data.size()) {}


    /*
    Overloads the * operator to access the current element.
    @return A const reference to the current element.
    @throws std::out_of_range if the iterator is out of range.
    */
    const T& operator*() const {
        if(index == 0) {
            throw std::out_of_range("Iterator is out of range");
        }
        return data[index-1]; // Access the element at the current index
    }
    /*
    Overloads the -> operator to access members of T.
    @return A pointer to the current element.
    @throws std::out_of_range if the iterator is out of range.
    */
    const T* operator->() const {
        if(index == 0) {
            throw std::out_of_range("Iterator is out of range");
        }
        return &data[index-1]; // Access the element at the current index
    }

    /*
    Overloads the ++ operator to move to the next element.
    @return A reference to the current iterator after incrementing it.
    @throws std::out_of_range if the iterator is already at the end of the container.
    */
    ReverseOrderIterator& operator++() {
        if (index == 0) {// If we are at the beginning, we cannot increment
            index=data.size();
        }
        else{
            --index;
        }
        return *this;
    }

    /*
    Overloads the -- operator to move to the previous element.
    @return A reference to the current iterator after decrementing it.
    @throws std::out_of_range if the iterator is already at the beginning of the container.
    */
    ReverseOrderIterator& operator--() {
        if (index >= data.size()) {// If we are at the end, we cannot decrement
            throw std::out_of_range("Cannot decrement iterator before the beginning");
        }
        ++index;
        return *this;
    }

    /*
    Overloads the post-increment operator to move to the next element.
    @return A copy of the current iterator before incrementing it.
    @throws std::out_of_range if the iterator is already at the end of the container.
    */
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

    /*
    Overloads the == operator to compare two ReverseOrderIterator objects.
    @param other The other iterator to compare with.
    @return true if the two iterators are equal, false otherwise.
    */
    bool operator==(const ReverseOrderIterator& other) const {
        return (index==other.index)&&(data==other.data);
    }
    /*
    Overloads the != operator to compare two ReverseOrderIterator objects.
    @param other The other iterator to compare with.
    @return true if the two iterators are not equal, false otherwise.
    */
    bool operator!=(const ReverseOrderIterator& other) const {
        return !(*this == other);
    }

};
}
#endif