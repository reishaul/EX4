#pragma once//same as #ifndef and #define
#include "MyContainer.hpp"

namespace Rei{
template <typename T>
class MyContainer;

template <typename T>

// SideCrossOrder Iterator
class MyContainer<T>::SideCrossOrderIterator {
private:
    vector<T> helper;
    size_t index;

public:
    SideCrossOrderIterator(const vector<T>& data, bool end = false){
        vector<T> sorted_data = data;
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
        return helper[index];
    }

    SideCrossOrderIterator& operator++() {
        index++;
        return *this;
    }

    bool operator!=(const SideCrossOrderIterator& other) const {
        return index != other.index;
    }
};
}