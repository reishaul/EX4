//reishaul1@gmail.com
#ifndef MYCONTAINER_HPP
#define MYCONTAINER_HPP
#include <vector>
#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <cstddef>

//using std::ostream_iterator;


namespace Rei {

    template <typename T=int>

    class MyContainer{

    private:
        std::vector<T> data;

    public:
        MyContainer()=default;
        ~MyContainer()=default;

        void addElement(const T& value) {data.push_back(value);}

        void removeElement(const T& value) {
            auto size_=data.size();
            //erase the valuse from the vector
            data.erase(std::remove(data.begin(), data.end(), value), data.end());

            if(data.size() == size_) {
                cout << "Value not found in the container" << endl;
            }
        }


        size_t size() const {return data.size();}

        void print(ostream& os=cout) const {
            os<<"[";
            for (size_t i = 0; i < data.size(); ++i) {
                os << data[i];
                if (i < data.size() - 1) {
                    os << ", ";
                }
            }
            os << "]" << std::endl;
        }

        

        friend std::ostream& operator<<(std::ostream& os, const MyContainer<T>& container) {
            container.print(os);
            return os;
        }

        class AscendingIterator;
        class SideCrossOrderIterator;
        class ReverseOrderIterator;
        class DescendingIterator;
        class MiddleOutOrderIterator;
        class OrderIterator;

        AscendingIterator begin_ascending_order() const {
            return AscendingIterator(data, false);
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
    };

}

// Iterator typedefs
#include "AscendingIterator.hpp"
#include "DescendingOrderIterator.hpp"
#include "OrderIterator.hpp"
#include "SideCrossOrderIterator.hpp"
#include "MiddleOutOrderIterator.hpp"
#include "ReverseOrderIterator.hpp"


#endif // MYCONTAINER_HPP