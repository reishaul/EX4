//reishaul1@gmail.com

#ifndef MYCONTAINER_HPP
#define MYCONTAINER_HPP

//include necessary headers
#include <vector>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <cstddef>

// Namespace for the container
namespace Rei {

    template <typename T=int>// Default type is int

    /*
    * A simple container class that holds elements of type T(generic type)
    * and provides various functionalities like adding, removing, iterating, etc.
    * It uses a vector to store the elements and provides iterators for different orders.
    * It also provides a print function to display the elements in the container.
    * The class is designed to be generic and can be used with any type that supports the required operations.
    */
    class MyContainer{

    private:
        std::vector<T> data;// Vector to hold the elements of type T

    public:
        MyContainer()=default;// Default constructor - initializes an empty container, can be used with any type T
        ~MyContainer()=default;// Destructor - cleans up the container, can be used with any type T

        // Copy constructor and assignment operator 
        // MyContainer(const MyContainer& other) = default;
        // MyContainer& operator=(const MyContainer& other) = default;

         // Move constructor and assignment operator
        // MyContainer(MyContainer&& other) noexcept = default;
        // MyContainer& operator=(MyContainer&& other) noexcept = default;


        /*
        @brief Adds an element to the container.
        @param value The value to be added to the container.
        @throws std::invalid_argument if the value is already present in the container.
        @note This function uses std::vector to store the elements and provides a simple way to add elements.
        */
        void addElement(const T& value) {data.push_back(value);}

        void removeElement(const T& value) {
            auto size_=data.size();
            //erase the values from the vector removing all occurrences of the value
            data.erase(std::remove(data.begin(), data.end(), value), data.end());

            if(data.size() == size_) {// If size didn't change, the element was not found
                throw std::invalid_argument("Element not found in the container");
            }
        }


        /*
        @return The number of elements in the container.
        */
        size_t size() const {return data.size();}

        /*
        @return True if the container is empty, false otherwise.
        */
        bool empty() const {
            return data.empty();
        }
        
        // Clear all elements
        void clear() {
            data.clear();
        }

        /*
        @return A const reference to the element at the specified index.
        @throws std::out_of_range if the index is invalid.//sign
        */
        const T& operator[](size_t index) const {
            if (index >= data.size()) {
                throw std::out_of_range("Index is out of range");
            }
            return data[index];
        }

        /*
        @brief Prints the elements in the container to the specified output stream
        @param os The output stream to print to (default is std::cout).
        @note This function iterates through the elements in the container and prints them in a formatted way.
        @example
        MyContainer<int> container;
        container.addElement(1);
        container.addElement(2);
        container.print(); // Output: [1, 2]
        */
        void print(std::ostream& os=std::cout) const {
            os<<"[";
            for (size_t i = 0; i < data.size(); ++i) {
                os << data[i];
                if (i < data.size() - 1) {
                    os << ", ";
                }
            }
            os << "]" << std::endl;
        }

        /*
        @brief Overloads the << operator to print the container.
        @param os The output stream to print to.
        @param container The container to print.
        @return The output stream.
        */
        friend std::ostream& operator<<(std::ostream& os, const MyContainer<T>& container) {
            container.print(os);
            return os;
        }

        // Iterator classes for different orders
        // Forward declarations of iterator classes
        // These classes will be defined in separate header files
        // to keep the MyContainer class clean and focused on its main functionality.
        // Each iterator class will implement the necessary functionality to iterate over the container
        class AscendingIterator;
        class DescendingIterator;
        class SideCrossOrderIterator;
        class ReverseOrderIterator;
        class MiddleOutOrderIterator;
        class OrderIterator;


        // Factory methods to create iterators for different orders
        // These methods return instances of the iterator classes, allowing users to iterate over the container in various orders.
        AscendingIterator begin_ascending_order() const {
            return AscendingIterator(data, false);// false indicates not at the end 
        }

        AscendingIterator end_ascending_order() const {
            return AscendingIterator(data, true);
        }

        
        DescendingIterator begin_descending_order() const {
            return DescendingIterator(data, false);
        }
    
        DescendingIterator end_descending_order() const {
            return DescendingIterator(data, true);
        }

        SideCrossOrderIterator begin_side_cross_order() const {
            return SideCrossOrderIterator(data, false);
        }

        SideCrossOrderIterator end_side_cross_order() const {
            return SideCrossOrderIterator(data, true);
        }

        // Reverse order iterator
        // These iterators allow users to traverse the container in reverse order, starting from the last element and moving to the first.
        // They are useful for scenarios where reverse traversal is needed, such as when processing elements in reverse order.
        ReverseOrderIterator begin_reverse_order() const {
            return ReverseOrderIterator(data, false);
        }

        ReverseOrderIterator end_reverse_order() const {
            return ReverseOrderIterator(data, true);
        }

        OrderIterator begin_order() const {
            return OrderIterator(data, false);
        }

        OrderIterator end_order() const {
            return OrderIterator(data, true);
        }

        MiddleOutOrderIterator begin_middle_out_order() const {
            return MiddleOutOrderIterator(data, false);
        }

        MiddleOutOrderIterator end_middle_out_order() const {
            return MiddleOutOrderIterator(data, true);
        }


        // Standard begin/end for range-based for loops
        auto begin() const { return data.begin(); }
        auto end() const { return data.end(); }
        
        // Get reference to underlying data (for iterator implementations)
        const std::vector<T>& getData() const { return data; }

    };

}

// Iterator typedefs forward declarations
// These typedefs provide convenient names for the iterator types, making it easier to use them in client code.
#include "Iterators/AscendingIterator.hpp"
#include "Iterators/DescendingIterator.hpp"
#include "Iterators/OrderIterator.hpp"
#include "Iterators/SideCrossOrderIterator.hpp"
#include "Iterators/MiddleOutOrderIterator.hpp"
#include "Iterators/ReverseOrderIterator.hpp"


#endif // MYCONTAINER_HPP