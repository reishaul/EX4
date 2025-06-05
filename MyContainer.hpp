//reishaul1@gmail.com
#ifndef MYCONTAINER_HPP
#define MYCONTAINER_HPP
#include <vector>
#include <algorithm>
#include <iostream>
#include <stdexcept>

using std::vector;
using std::ostream;
using std::cout;
using std::endl;
//using std::ostream_iterator;


namespace Rei {

    template <typename T=int>

    class MyContainer{

    private:
        vector<T> data;

    public:

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



        // Ascending Iterator 
        class AscendingIterator {
        private:
            std::vector<T> sorted;
            size_t index;

        public:
            AscendingIterator(const vector<T>& original, bool end = false)
                : sorted(original) {
                std::sort(sorted.begin(), sorted.end());// Sort in ascending order by default
                // If end is true, set index to the size of the sorted vector, otherwise set it to 0
                index = end ? sorted.size() : 0;
            }

            const T& operator*() const {
                return sorted[index];
            }

            AscendingIterator& operator++() {
                ++index;
                return *this;
            }

            bool operator!=(const AscendingIterator& other) const {
                return index != other.index;
            }
        };

        AscendingIterator begin_ascending_order() const {
            return AscendingIterator(data, false);
        }

        AscendingIterator end_ascending_order() const {
            return AscendingIterator(data, true);
        }


        // Descending Iterator 
        class DescendingIterator {
        private:
            std::vector<T> sorted;
            size_t index;

        public:
            DescendingIterator(const std::vector<T>& original, bool end = false)
                : sorted(original) {
                std::sort(sorted.begin(), sorted.end(), std::greater<T>());
                index = end ? sorted.size() : 0;
            }

            const T& operator*() const {
                return sorted[index];
            }

            DescendingIterator& operator++() {
                ++index;
                return *this;
            }

            bool operator!=(const DescendingIterator& other) const {
                return index != other.index;
            }
        };

        DescendingIterator begin_descending_order() const {
            return DescendingIterator(data, false);
        }

    
        DescendingIterator end_descending_order() const {
            return DescendingIterator(data, true);
        }

        // SideCrossOrder Iterator
        class SideCrossOrderIterator {
        private:
            const vector<T>& data;
            size_t index;

        public:
            SideCrossOrderIterator(const std::vector<T>& data, bool end = false)
                : data(data), index(end ? data.size() : 0) {
                vector<T> sorted_data = data;
                std::sort(sorted_data.begin(), sorted_data.end());//first sort the data

                size_t left = 0;
                size_t right = sorted_data.size() - 1;
                sixe_t i=0;

                //
                while(left<=right){
                    if(left == right) {
                        // If both pointers meet, add the last element
                        data.push_back(sorted_data[left]);
                        break;
                    }
                    else {
                        data.push_back(sorted_data[left]);
                        data.push_back(sorted_data[right]);
                    }
                    left++;
                    right--;
                    if(right<=0) break;
                }
                if(end) {index = data.size();}
                    
            }
            
            const T& operator*() const {
                return data[index];
            }

            SideCrossOrderIterator& operator++() {
                index++;
                return *this;
            }

            bool operator!=(const SideCrossOrderIterator& other) const {
                return index != other.index;
            }
        };

        SideCrossOrderIterator begin_side_cross_order() const {
            return SideCrossOrderIterator(data, false);
        }

        SideCrossOrderIterator end_side_cross_order() const {
            return SideCrossOrderIterator(data, true);
        }



        // ReverseOrder Iterator
        class ReverseOrderIterator {
        private:
            const vector<T>& data;
            size_t index;

        public:
            // Constructor that initializes the iterator to the end or beginning of the data
            ReverseOrderIterator(const vector<T>& data, bool end = false)
                : data(data), index(end ? data.size() : 0) {
                    for(size_t i = 0; i < data.size(); ++i) {
                        

                        T tmp;
                        size_t j = 0;
                        while(j<data.size()) {
                            tmp=data[j];
                            data.push_back(data[data.size() - 1 - j]);
                            data[data.size() - 1 - j] = tmp;
                            j++;
                        }
                    }


                }

            const T& operator*() const {
                return data[index];
            }

            ReverseOrderIterator& operator++() {
                index++;
                return *this;
            }

            bool operator!=(const ReverseOrderIterator& other) const {
                return index != other.index;
            }
        };

        ReverseOrderIterator begin_reverse_order() const {
            return ReverseOrderIterator(data, false);
        }

        ReverseOrderIterator end_reverse_order() const {
            return ReverseOrderIterator(data, true);
        }
    };

}

#endif // MYCONTAINER_HPP