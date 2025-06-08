//reishaul1@gmail.com
#ifndef ORDER_ITERATOR_HPP
#define ORDER_ITERATOR_HPP

#include "../MyContainer.hpp"
#include <iterator>
#include <stdexcept>

//this file defines the OrderIterator class for the MyContainer class.
// The OrderIterator allows iteration over the elements of MyContainer in the order they were added.
// It provides functionality to traverse the container in a linear fashion, starting from the first element to the last.
namespace Rei{

//forward declaration of MyContainer class
// This is necessary to allow the OrderIterator class to access the private members of MyContainer.
template <typename T>
class MyContainer;

template<typename T>// A template class for the OrderIterator

// Order Iterator
class MyContainer<T>::OrderIterator {// a nested class of MyContainer
//objects of this class can only be accessed by MyContainer class
private:
    const std::vector<T>& data;
    size_t index;

public:
    // Constructor that initializes the iterator to the end or beginning of the data
    OrderIterator(const std::vector<T>& data, bool end = false)
        : data(data), index(end ? data.size() : 0) {}


    /*
    @brief Overloads the * operator to access the current element.
    @return A reference to the current element in the container.
    @throws std::out_of_range if the iterator is out of range.
    */
    const T& operator*() const {
        if(index >= data.size()) {// Check if the index is out of range
            throw std::out_of_range("Iterator is out of range");
        }
        return data[index];// Access the element at the current index
    }

    /*
    same as above but returns a pointer to the current element
    */
    const T* operator->() const{
        if(index >= data.size()) {// Check if the index is out of range
            throw std::out_of_range("Iterator is out of range");
        }
        return &data[index];// Return a pointer to the current element
    } 
    /*
    Overloads the ++ operator to move to the next element.
    @return A reference to the current iterator after incrementing it.
    @throws std::out_of_range if the iterator is already at the end of the container.
    */
    OrderIterator& operator++() {
        if (index >= data.size()) {
            throw std::out_of_range("Iterator is out of range");
        }
        index++;
        return *this;
    }

    /*
    Overloads the -- operator to move to the previous element.
    @return A reference to the current iterator after decrementing it.
    @throws std::out_of_range if the iterator is already at the beginning of the container.
    */
    OrderIterator& operator--() {
        if (index == 0) {
            throw std::out_of_range("Cannot decrement iterator before the beginning");
        }
        --index;
        return *this;
    }
    /*
    Overloads the post-increment operator to move to the next element.
    @return A copy of the current iterator before incrementing it.
    @throws std::out_of_range if the iterator is already at the end of the container.
    */
    OrderIterator operator++(int) {
        if (index >= data.size()) {
            throw std::out_of_range("Iterator is out of range");
        }
        // Create a copy of the current iterator
        // and then increment the current iterator
        OrderIterator temp = *this;
        ++(*this);
        return temp;
    }
    /*
    Overloads the == operator to compare two OrderIterator objects.
    @param other The other iterator to compare with.
    @return true if the two iterators are equal, false otherwise.
    */
    bool operator==(const OrderIterator& other)const{
        return (index==other.index)&&(data==other.data);
    }

    /*
    Overloads the != operator to compare two OrderIterator objects.
    @param other The other iterator to compare with.
    @return true if the two iterators are not equal, false otherwise.
    */
    bool operator!=(const OrderIterator& other) const {
        return !(*this==other);
    }
};

}
#endif
