//reishaul1@gmail.com
#ifndef MIDDLE_OUT_ORDER_ITERATOR_HPP
#define MIDDLE_OUT_ORDER_ITERATOR_HPP

#include "../MyContainer.hpp"// Include the MyContainer header to access its members
#include <iterator>
#include <stdexcept>

/*
this file defines the MiddleOutOrderIterator class for the MyContainer class.
the MiddleOutOrderIterator allows iteration over the elements of MyContainer in a middle-out order.
*/
namespace Rei{

// Forward declaration of MyContainer class
// This is necessary to allow the MiddleOutOrderIterator class to access the private members of MyContainer.
template <typename T>
class MyContainer;

template<typename T>//a template class for the MiddleOutOrderIterator

// Middle Out Order Iterator
// This class implements an iterator that traverses the elements of MyContainer in a middle-out order.
// The middle-out order starts from the middle element and alternates between left and right elements, moving outward.
class MyContainer<T>::MiddleOutOrderIterator {// a nested class of MyContainer

private:// Objects of this class can only be accessed by MyContainer class
    const std::vector<T>& data;
    //sizes of the data vector and the middle index
    size_t middle;
    size_t move;

public:
    // Constructor that initializes the iterator to the end or beginning of the data
    //at the initialization it define the middle index and the move index according to the given parameters
    MiddleOutOrderIterator(const std::vector<T>& data, bool end = false)
        : data(data), middle((data.size() % 2 == 0) ? (data.size() / 2 - 1) : (data.size() / 2)), move(end?data.size():0){}

    /*
    Overloads the * operator to access the current element.
    @returns a const reference to the current element.
    @throws std::out_of_range if the iterator is out of range.
    @note If the move is 0, it returns the middle element.
    If the move is greater than 0, it calculates the index based on the move and returns the corresponding element.
    The index is calculated based on whether the move is even or odd, determining whether to go left or right from the middle.
    */
    const T& operator*() const {

        if(move==0){return data[middle];} // If move is 0, return the middle element
        size_t i=(move+1)/2;

        bool goLeft = (move % 2 == 1);//if true so go left, and if false so go right

        int index;//to store the index which is calculated
        if(goLeft){
            index= (int)middle - (int)i; // Calculate the index for even moves
        } else {
            index = (int)middle + (int)i; // Calculate the index for odd moves
        } // Calculate the index based on the move
        
        return data[index];// Access the element at the current index
    }

    /*
    same as the operator* but returns a pointer to the current element.
    @returns a pointer to the current element.
    @throws std::out_of_range if the iterator is out of range.
    */
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

    /*
    Overloads the ++ operator to move to the next element.
    @returns a reference to the current iterator after incrementing it.
    @throws std::out_of_range if the iterator is already at the end of the container.
    */
    MiddleOutOrderIterator& operator++() {
        if (move >= data.size()) {//first check if the iterator is already at the end of the container
            throw std::out_of_range("Iterator is out of range");
        }
        move++;// Increment the move index to point to the next element
        return *this;
    }

    /*
    Overloads the post-decrement operator to move to the previous element.
    @return a copy of the current iterator before decrementing it.
    @throws std::out_of_range if the iterator is already at the beginning of the container.
    */
    MiddleOutOrderIterator& operator--() {
        if (move == 0) {// Check if the iterator is already at the beginning
            throw std::out_of_range("Cannot decrement iterator before the beginning");
        }
        move--;// Decrement the move index to point to the previous element
        return *this;
    }

    /*
    Overloads the post-increment operator to move to the next element.
    @return a copy of the current iterator before incrementing it.
    @throws std::out_of_range if the iterator is already at the end of the container.
    */
    MiddleOutOrderIterator operator++(int){
        if (move >= data.size()) {
            throw std::out_of_range("Iterator is out of range");
        }
        MiddleOutOrderIterator tmp=*this;//save the current state of the iterator
        ++(*this);//move to the next element
        return tmp;//return the saved state of the iterator
    }

    /*
    overload == operator to compare two MiddleOutOrderIterator objects.
    @param other The other iterator to compare with.
    @return true if the two iterators are equal, false otherwise.
    */
    bool operator==(const MiddleOutOrderIterator& other) const {
        return (move == other.move) && (data == other.data);
    }

    /*
    overload != operator to compare two MiddleOutOrderIterator objects.
    @param other The other iterator to compare with.
    @return true if the two iterators are not equal, false otherwise.
    */
    bool operator!=(const MiddleOutOrderIterator& other) const {
        return !(*this == other);
    }

};
}
#endif