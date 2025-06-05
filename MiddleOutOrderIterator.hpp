#ifndef MIDDLE_OUT_ORDER_ITERATOR_HPP
#define MIDDLE_OUT_ORDER_ITERATOR_HPP

#include "MyContainer.hpp"

namespace Rei{
template <typename T>
class MyContainer;

template<typename T>

// Middle Out Order Iterator
class MyContainer<T>::MiddleOutOrderIterator {
private:
    const vector<T>& data;
    size_t middle;
    size_t move;

public:
    // Constructor that initializes the iterator to the end or beginning of the data
    MiddleOutOrderIterator(const vector<T>& data, bool end = false)
        : data(data), middle((data.size() % 2 == 0) ? (data.size() / 2 - 1) : (data.size() / 2)), move(end?data.size():0){}

    const T& operator*() const {

        if(move==0){return data[middle];} // If move is 0, return the middle element
        size_t i=(move+1)/2;

        bool goLeft = (move % 2 == 0);//if true so go left, and if false so go right
        //int a=(move+1)/2;
        int index;
        if(goLeft){
            index= (int)middle - (int)i; // Calculate the index for even moves
        } else {
            index = (int)middle + (int)i; // Calculate the index for odd moves
        } // Calculate the index based on the move
        
        return data[index];// Access the element at the current index
    }

    MiddleOutOrderIterator& operator++() {
        move++;
        return *this;
    }

    bool operator!=(const MiddleOutOrderIterator& other) const {
        return move != other.move;
    }
};

}
#endif