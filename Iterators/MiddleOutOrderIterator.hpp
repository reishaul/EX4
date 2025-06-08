//reishaul1@gmail.com
#ifndef MIDDLE_OUT_ORDER_ITERATOR_HPP
#define MIDDLE_OUT_ORDER_ITERATOR_HPP

#include "../MyContainer.hpp"
#include <iterator>
#include <stdexcept>

namespace Rei{

template <typename T>
class MyContainer;

template<typename T>

// Middle Out Order Iterator
class MyContainer<T>::MiddleOutOrderIterator {
private:
    const std::vector<T>& data;
    size_t middle;
    size_t move;

public:
    // Constructor that initializes the iterator to the end or beginning of the data
    MiddleOutOrderIterator(const std::vector<T>& data, bool end = false)
        : data(data), middle((data.size() % 2 == 0) ? (data.size() / 2 - 1) : (data.size() / 2)), move(end?data.size():0){}

    const T& operator*() const {

        if(move==0){return data[middle];} // If move is 0, return the middle element
        size_t i=(move+1)/2;

        bool goLeft = (move % 2 == 1);//if true so go left, and if false so go right

        int index;
        if(goLeft){
            index= (int)middle - (int)i; // Calculate the index for even moves
        } else {
            index = (int)middle + (int)i; // Calculate the index for odd moves
        } // Calculate the index based on the move
        
        return data[index];// Access the element at the current index
    }

    const T* operator->() const{

        if(move==0){return data[middle];} // If move is 0, return the middle element
        size_t i=(move+1)/2;

        bool goLeft = (move % 2 == 1);//if true so go left, and if false so go right

        int index;
        if(goLeft){
            index= (int)middle - (int)i; // Calculate the index for even moves
        } else {
            index = (int)middle + (int)i; // Calculate the index for odd moves
        } // Calculate the index based on the move
        
        return &data[index];// Access the element at the current index

    }

    MiddleOutOrderIterator& operator++() {
        if (move >= data.size()) {
            throw std::out_of_range("Iterator is out of range");
        }
        move++;
        return *this;
    }

    MiddleOutOrderIterator& operator--() {
        if (move == 0) {
            throw std::out_of_range("Cannot decrement iterator before the beginning");
        }
        move--;
        return *this;
    }

    MiddleOutOrderIterator operator++(int){
        if (move >= data.size()) {
            throw std::out_of_range("Iterator is out of range");
        }
        MiddleOutOrderIterator tmp=*this;
        ++(*this);
        return tmp;
    }

    bool operator==(const MiddleOutOrderIterator& other) const {
        return (move == other.move) && (&data == &other.data);
    }

    bool operator!=(const MiddleOutOrderIterator& other) const {
        return !(*this == other);
    }

};

}
#endif