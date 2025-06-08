//reishaul1@gmail.com
#pragma once//same as #ifndef and #define

#include "../MyContainer.hpp"
#include <iterator>
#include <stdexcept>

namespace Rei {

template <typename T>
class MyContainer;

template <typename T>

// SideCrossOrder Iterator
class MyContainer<T>::SideCrossOrderIterator {//nested class to MyContainer
private:
    std::vector<T> helper;// Helper vector to store the side-cross order elements
    size_t index;

public:
    SideCrossOrderIterator(const std::vector<T>& data, bool end = false){
        std::vector<T> sorted_data = data;
        std::sort(sorted_data.begin(), sorted_data.end());//first sort the data

        size_t left = 0;
        size_t right = sorted_data.size() - 1;

        //
        while(left<=right){
            if(left == right) {
                // If both pointers meet, add the last element
                helper.push_back(sorted_data[left]);
            }
            else {
                helper.push_back(sorted_data[left]);
                helper.push_back(sorted_data[right]);
            }
            ++left;
            
            if(right>0) { right--;}// Decrement right pointer only if it's greater than 0
        }
        index = end ? helper.size() : 0; // If end is true, set index to the size of the helper vector, otherwise set it to 0
    }
    
    const T& operator*() const {
        if (index >= helper.size()) {
            throw std::out_of_range("Iterator is out of range");
        }
        return helper[index];
    }

    const T* operator->() const {
        if (index >= helper.size()) {
            throw std::out_of_range("Iterator is out of range");
        }
        return &helper[index];
    }



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
    SideCrossOrderIterator& operator--() {
        if (index == 0) {
            throw std::out_of_range("Cannot decrement iterator before the beginning");
        }
        --index;
        return *this;
    }

    SideCrossOrderIterator operator++(int) {
        if (index >= helper.size()) {
            throw std::out_of_range("Iterator is out of range");
        }
        SideCrossOrderIterator temp = *this;
        ++(*this);
        return temp;
    }

    bool operator!=(const SideCrossOrderIterator& other) const {
        return !(*this == other);
    }

    bool operator==(const SideCrossOrderIterator& other) const {
        return (helper == other.helper) && (index == other.index);
    }

};
}