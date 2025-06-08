//reishaul1@gmail.com
#pragma once//same as #ifndef and #define

#include "../MyContainer.hpp"// Include the MyContainer class definition
#include <iterator>
#include <stdexcept>

// This file defines the SideCrossOrderIterator class for the MyContainer class.
// The SideCrossOrderIterator allows iteration over the elements of MyContainer in a side-cross order.
namespace Rei {

// Forward declaration of MyContainer class
// This is necessary to allow the SideCrossOrderIterator class to access the private members of MyContainer.
template <typename T>
class MyContainer;

template <typename T>// A template class for the SideCrossOrderIterator

// SideCrossOrder Iterator
class MyContainer<T>::SideCrossOrderIterator {//nested class to MyContainer
private:// Objects of this class can only be accessed by MyContainer class
    std::vector<T> helper;// Helper vector to store the side-cross order elements
    size_t index;

public:
// Constructor that initializes the iterator with the original vector
// It sorts the data and arranges it in a side-cross order.
    SideCrossOrderIterator(const std::vector<T>& data, bool end = false){
        std::vector<T> sorted_data = data;
        std::sort(sorted_data.begin(), sorted_data.end());//first sort the data
        //two indexes to traverse the sorted data from both ends
        size_t left = 0;
        size_t right = sorted_data.size() - 1;

        //keep looping until left pointer is less than or equal to right pointer
        while(left<=right){
            if(left == right) {// If both pointers meet, add the last element
                // If both pointers meet, add the last element
                helper.push_back(sorted_data[left]);
            }
            else {// If pointers are not equal, add elements from left and then right
                helper.push_back(sorted_data[left]);
                helper.push_back(sorted_data[right]);
            }
            ++left;
            
            if(right>0) { right--;}// Decrement right pointer only if it's greater than 0
        }
        index = end ? helper.size() : 0; // If end is true, set index to the size of the helper vector, otherwise set it to 0
    }

    /*
    Overloads the * operator to access the current element.
    @return A const reference to the current element.
    @throws std::out_of_range if the iterator is out of range.
    */
    const T& operator*() const {
        if (index >= helper.size()) {
            throw std::out_of_range("Iterator is out of range");
        }
        return helper[index];
    }

    /*
    Overloads the -> operator to access members of T.
    @return A pointer to the current element.
    @throws std::out_of_range if the iterator is out of range.
    */
    const T* operator->() const {
        if (index >= helper.size()) {
            throw std::out_of_range("Iterator is out of range");
        }
        return &helper[index];
    }

    /*
    Overloads the ++ operator to move to the next element.
    @returns a reference to the current iterator after incrementing it.
    @throws std::out_of_range if the iterator is already at the end of the container.
    */
    SideCrossOrderIterator& operator++() {
        if (index >= helper.size()) {
            throw std::out_of_range("Iterator is out of range");
        }
        // Increment the index only if it's less than the size of the helper vector
        // This prevents out-of-bounds access
        if(index < helper.size()) {
            ++index;
        } 
        return *this;
    }

    /*
    Overloads the -- operator to move to the previous element.
    @returns a reference to the current iterator after decrementing it.
    @throws std::out_of_range if the iterator is already at the beginning of the container.
    */
    SideCrossOrderIterator& operator--() {
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
    SideCrossOrderIterator operator++(int) {
        if (index >= helper.size()) {
            throw std::out_of_range("Iterator is out of range");
        }
        SideCrossOrderIterator temp = *this;
        ++(*this);
        return temp;
    }

    /*
    Overloads the != operator to compare two SideCrossOrderIterator objects.
    @param other The other iterator to compare with.
    @return true if the two iterators are not equal, false otherwise.
    */
    bool operator!=(const SideCrossOrderIterator& other) const {
        return !(*this == other);
    }

    /*
    Overloads the == operator to compare two SideCrossOrderIterator objects.
    @param other The other iterator to compare with.
    @return true if the two iterators are equal, false otherwise.
    */
    bool operator==(const SideCrossOrderIterator& other) const {
        return (helper == other.helper) && (index == other.index);
    }

};
}