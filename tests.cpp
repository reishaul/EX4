//reishaul1@gmail.com
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "MyContainer.hpp"

using namespace Rei;

TEST_CASE("MyContainer basic operations") {
    MyContainer<int> container;
    //first adding elements to the container
    SUBCASE("Add elements") {
        container.addElement(10);
        container.addElement(20);
        container.addElement(30);
        CHECK(container.size() == 3);// Check if the size is correct
    }

    SUBCASE("Remove elements") {// Removing elements from the container
        container.addElement(10);
        container.addElement(20);
        container.removeElement(10);
        CHECK(container.size() == 1);
        CHECK_THROWS_AS(container.removeElement(100), std::invalid_argument);//try to remove an element that does not exist in the container
        CHECK_THROWS_WITH(container.removeElement(100), "Element not found in the container");
    }

    SUBCASE("Check empty") {
        CHECK(container.empty());//using empty function to check if the container is empty
        container.addElement(10);
        CHECK(!container.empty());
    }

    SUBCASE("Clear elements") {
        container.addElement(10);
        container.clear();//using clear function to remove all elements from the container
        CHECK(container.size() == 0);//new
        CHECK(container.empty());
    }
    SUBCASE("Access elements") {
        container.addElement(10);
        container.addElement(20);
        CHECK(container[0] == 10);//checking the [] operator for accessing elements
        CHECK(container[1] == 20);
    }

    SUBCASE("Print elements") {
        container.addElement(10);
        container.addElement(20);
        std::ostringstream oss;
        container.print(oss);//checking the print function implementation
        CHECK(oss.str() == "[10, 20]\n");
    }
}

TEST_CASE("MyContainer check iterators correctness") {
    MyContainer<int> container;
    container.addElement(10);
    container.addElement(20);
    container.addElement(30);
    container.addElement(40);
    container.addElement(50);

    SUBCASE("Reverse order iterator") {// Testing reverse order iterator
        auto it = container.begin_reverse_order();
        CHECK(*it == 50);// Check if the first element is 50 before incrementing
        ++it;
        CHECK(*it == 40);// Check if the second element is 40
        ++it;
        CHECK(*it == 30);// Check if the third element is 30
        ++it;
        CHECK(*it == 20);// Check if the fourth element is 20
        ++it;
        CHECK(*it == 10);// Check if the fifth element is 10
        ++it;
        CHECK(it == container.end_reverse_order());// Check if the iterator is at the end
    }

    SUBCASE("Side cross order iterator") {
        auto it = container.begin_side_cross_order();
        CHECK(*it == 10);// Check if the first element is 10 before incrementing
        ++it;
        CHECK(*it == 50);// Check if the second element is 50
        ++it;
        CHECK(*it == 20);// Check if the third element is 20
        ++it;
        CHECK(*it == 40);// Check if the fourth element is 40
        ++it;
        CHECK(*it == 30);// Check if the fifth element is 30
        ++it;
        CHECK(it == container.end_side_cross_order());
    }

    SUBCASE("Ascending order iterator special case") {// Testing ascending order iterator
        MyContainer<int> container1; // Create a new container for ascending order test
        // Adding elements in ascending order

        container1.addElement(10);
        container1.addElement(20);
        container1.addElement(10);//same element added multiple times
        container1.addElement(20);//same element added multiple times
        container1.addElement(10);
        // The elements are already in ascending order
        auto it5 = container1.begin_ascending_order();
        CHECK(*it5 == 10);
        ++it5;
        CHECK(*it5 == 10);
        ++it5;
        CHECK(*it5 == 10);
        ++it5;
        CHECK(*it5 == 20);
        ++it5;
        CHECK(*it5 == 20);
        ++it5;
        CHECK(it5 == container1.end_ascending_order());
    }

    SUBCASE("Ascending order iterator") {// Testing ascending order iterator

        MyContainer<int> container1; // Create a new container for ascending order test
        // Adding elements in ascending order

        container1.addElement(10);
        container1.addElement(-20);
        container1.addElement(190);//same element added multiple times
        container1.addElement(190);//same element added multiple times
        container1.addElement(5);
        // The elements are already in ascending order
        auto it = container1.begin_ascending_order();
        //adding different elements to the container
        CHECK(*it == -20);
        ++it;
        CHECK(*it == 5);
        ++it;
        CHECK(*it == 10);
        ++it;
        CHECK(*it == 190);
        ++it;
        CHECK(*it == 190);
        ++it;
        CHECK(it == container1.end_ascending_order());
    }

    SUBCASE("Descending order iterator") {
        auto it = container.begin_descending_order();//creating a descending order iterator
        CHECK(*it == 50);//check if the biiggest element is first
        ++it;
        CHECK(*it == 40);
        ++it;
        CHECK(*it == 30);
        ++it;
        CHECK(*it == 20);
        ++it;
        CHECK(*it == 10);//check if the smallest element is last
        ++it;
        CHECK(it == container.end_descending_order());// Check if the iterator is at the end
    }

    SUBCASE("container that each element is a key and value pair"){
        struct numbers{//creating a struct to hold key-value pairs
            std::string key;
            int value;
            // Overloading comparison operators for sorting
            // This is necessary for the MyContainer to sort the elements correctly
            bool operator<(const numbers& other) const {
                return value < other.value;
            }
            // Overloading comparison operators for sorting
            bool operator>(const numbers& other) const {
                return value > other.value;
            }
            // Overloading equality operator to compare two numbers objects
            bool operator==(const numbers& other) const {
                return value == other.value && key == other.key;
            }
        };
        //adding key-value pairs to the container
        MyContainer<numbers> KVContainer;
        KVContainer.addElement({"thirty", 30});
        KVContainer.addElement({"ten", 10});
        KVContainer.addElement({"forty", 40});
        KVContainer.addElement({"twenty", 20});
        KVContainer.addElement({"fifty", 50});

        auto it = KVContainer.begin_descending_order();
        //the sort is according to the value of the key-value pair
        CHECK(*it == numbers{"fifty", 50}); // Check if the biggest element is first
        ++it;
        CHECK(*it == numbers{"forty", 40});
        ++it;
        CHECK(*it == numbers{"thirty", 30});
        ++it;
        CHECK(*it == numbers{"twenty", 20});
        ++it;
        CHECK(*it == numbers{"ten", 10});// Check if the smallest element is last
        ++it;
        CHECK(it == KVContainer.end_descending_order());

    }

    SUBCASE("Middle out order iterator") {
        //this iterator starts from the middle and then goes to the left and right
        auto it = container.begin_middle_out_order();
        CHECK(*it == 30);// Check if the middle element is first
        ++it;
        CHECK(*it == 20);// Check if the next element is 20(left of middle)
        ++it;
        CHECK(*it == 40);// Check if the next element is 40(right of middle)
        ++it;
        CHECK(*it == 10);
        ++it;
        CHECK(*it == 50);
        ++it;
        CHECK(it == container.end_middle_out_order());
    }

    SUBCASE("Order iterator") {//regular order iterator
        //this iterator goes from the first element to the last element
        auto it = container.begin_order();
        CHECK(*it == 10);//check if the first element is the first that is added
        ++it;
        CHECK(*it == 20);
        ++it;
        CHECK(*it == 30);
        ++it;
        CHECK(*it == 40);
        ++it;
        CHECK(*it == 50);//check if the last element is the last that is added
        ++it;
        CHECK(it == container.end_order());
    }
}

TEST_CASE("special cases"){
    MyContainer<int> container;


    SUBCASE("empty container"){
        auto it = container.begin();//the begin is also the end for an empty container
        CHECK(it == container.end());
    }

    container.addElement(5);//adding an element to the container
    SUBCASE("container with one element"){
        auto it = container.begin_reverse_order();
        for (; it != container.end_reverse_order(); ++it) {//only one iteration is needed
            CHECK(*it == 5);// Check if the only element is 5
        }
        CHECK(it==container.end_reverse_order());
    }

    MyContainer<> str;
    //str.addElement("abc");//cannot add string to int container
    str.addElement('r');//adding characters to the container
    str.addElement('e');
    str.addElement('i');

    SUBCASE("operator ->"){// Testing the -> operator 
        struct numbers{//creating a struct to hold key-value pairs
            std::string key;
            int value;
            // Overloading comparison operators for sorting
            // This is necessary for the MyContainer to sort the elements correctly
            bool operator<(const numbers& other) const {
                return value < other.value;
            }
            // Overloading comparison operators for sorting
            bool operator>(const numbers& other) const {
                return value > other.value;
            }
            // Overloading equality operator to compare two numbers objects
            bool operator==(const numbers& other) const {
                return value == other.value && key == other.key;
            }
        };
        MyContainer<numbers> KVContainer;//new container for key-value pairs
        //adding key-value pairs to the container
        KVContainer.addElement({"thirty", 30});
        KVContainer.addElement({"ten", 10});
        KVContainer.addElement({"forty", 40});
        auto it = KVContainer.begin_reverse_order();

        CHECK(it->key == "forty");//using the -> operator to access the key and value of the key-value pair
        CHECK(it->value == 40);
        ++it;
        CHECK(it->key == "ten");//the next element is ten according  to reverse order
        CHECK(it->value == 10);
        ++it;//going to the next element
        CHECK(it->key == "thirty");
        CHECK(it->value == 30);
        ++it;
    }

    SUBCASE("operator *"){// Testing the * operator 
        auto it = str.begin_middle_out_order();

        CHECK(*it=='e');//check if the middle element is first
        ++it;
        CHECK(*it=='r');//check if the next element is r(left of middle)
        ++it;
        CHECK(*it=='i');//check if the next element is i(right of middle)
    }

    SUBCASE("operator ++"){// Testing the pre-increment operator ++
        auto it = str.begin_order();
        CHECK(*it=='r');//check if the first element is r according to the regular order
        ++it;
        CHECK(*it=='e');//check if the next element is e
        ++it;
        CHECK(*it=='i');//check if the next element is i

        // expected output: B
    }

    // Testing the post-increment operator ++
    // This is a separate test case to ensure the post-increment works correctly
    SUBCASE("post increment operator ++"){
        auto it = str.begin_order();
        CHECK(*it=='r');//check if the first element is r according to the regular order
        it++;//post increment
        CHECK(*it=='e');//check if the next element is e
        it++;
        CHECK(*it=='i');
        it++;
        CHECK(it==str.end_order());// Check if the iterator is at the end
    }


    SUBCASE("operator --"){// Testing the pre-decrement operator --
        auto it = str.begin_order();
        ++it;// Increment to the second element
        ++it;// Increment to the third element
        CHECK(*it=='i');//check if the current element is i
        --it;//go one element back 
        CHECK(*it=='e');//check if the current element is e
        --it;//go one element back
        CHECK(*it=='r');//check if the current element is r
        //--it; // This will throw an exception since it goes before the beginning
        CHECK_THROWS_AS(--it, std::out_of_range);//one more decrement will throw an exception
        CHECK_THROWS_WITH(--it, "Cannot decrement iterator before the beginning");

    }

    SUBCASE("INT AS A DEFAULT &access overload[]"){
        MyContainer<> s;

        CHECK_NOTHROW(s.addElement('A'));//adding char to the container is allowed
        CHECK_NOTHROW(s.addElement('B'));
        CHECK_NOTHROW(s.addElement(5));//adding int to the  same container is allowed
        CHECK(s.size() == 3);
        CHECK(s[1]=='B');//checking the second element is B and also check the [] operator works correctly
        CHECK(s[2]==5);

        CHECK_NOTHROW(s.addElement(5.96));//adding double to the same container is allowed
        CHECK(s.size() == 4);
        CHECK(s[3]==5);//double is converted to int when added to the container

    }

    SUBCASE("operator == & != "){// Testing the equality and inequality operators
        MyContainer<> str;
        //adding characters to the container
        str.addElement('a');
        str.addElement('B');
        str.addElement('c');
        str.addElement('d');
        //initializing two iterators
        auto it = str.begin_order();
        auto it2 = str.begin_order();
        CHECK(it==it2);//first they are on the same element
        ++it;// Increment the first iterator
        CHECK(it!=it2);// Now they are on different elements
        CHECK(it2!=str.end_order());
        ++it2;// Increment the second iterator
        CHECK(it==it2);// Now they are on the same element again
        ++it2;
        CHECK(it!=it2);
        ++it2;
        CHECK(it!=it2);
        --it;
        ++it2;

        CHECK_THROWS_AS(++it2, std::out_of_range);// Incrementing the second iterator beyond the end will throw an exception
        CHECK_THROWS_WITH(++it2, "Iterator is out of range");


        //creating two containers with different elements
        MyContainer<int> c2;
        c2.addElement(1);
        c2.addElement(2);
        MyContainer<int> c3;
        c3.addElement(1);
        c3.addElement(3);

        // Testing equality and inequality operators with different containers
        auto it3 = c2.begin_order();
        auto it4 = c3.begin_order();

        CHECK(*it3==*it4);//check that the values are equal
        ++it3;
        ++it4;
        CHECK(*it3!=*it4);//the last elements are not equal

    }
}

TEST_CASE("test print function") {//checking the print function implementation
    MyContainer<int> container;//container with integers
    container.addElement(1);
    container.addElement(2);
    container.addElement(3);

    
    std::ostringstream oss;
    container.print(oss);//using the print function to print the elements of the container
    CHECK(oss.str() == "[1, 2, 3]\n");// Check if the output is correct

    // Test with an empty container
    MyContainer<int> emptyContainer;
    std::ostringstream emptyOss;
    emptyContainer.print(emptyOss);//using the print function to print the elements of the empty container
    CHECK(emptyOss.str() == "[]\n");// Check if the output for an empty container is correct 
}

TEST_CASE("test operator <<") {
    MyContainer<int> container;//creating a container with integers
    container.addElement(1);
    container.addElement(2);
    container.addElement(3);

    std::ostringstream oss;
    oss << container;// using the operator << to print the elements of the container
    CHECK(oss.str() == "[1, 2, 3]\n");// Check if the output is correct

    // Test with an empty container
    MyContainer<int> emptyContainer;
    std::ostringstream emptyOss;
    emptyOss << emptyContainer;// using the operator << to print the elements of the empty container
    CHECK(emptyOss.str() == "[]\n");// Check if the output for an empty container is correct
}

TEST_CASE("TEST adding strings to MyContainer") {// Testing the MyContainer with strings
    MyContainer<std::string> strContainer;//creating a container with strings
    CHECK_NOTHROW(strContainer.addElement("Hello")); // Adding strings to the container
    CHECK_NOTHROW(strContainer.addElement("World"));
    CHECK_NOTHROW(strContainer.addElement("!"));

    std::ostringstream oss;
    strContainer.print(oss);//using the print function to print the elements of the string container
    CHECK(oss.str() == "[Hello, World, !]\n");
    CHECK(strContainer.size() == 3);//there is three elements in the string container
    strContainer.removeElement("World");//removing an element from the string container
    CHECK(strContainer.size() == 2);//need to remain with two elements

    // Test with an empty string container
    MyContainer<std::string> emptyStrContainer;
    std::ostringstream emptyStrOss;
    emptyStrContainer.print(emptyStrOss);//using the print function to print the elements of the empty string container
    CHECK(emptyStrOss.str() == "[]\n");//need to get an empty string
    CHECK(emptyStrContainer.size() == 0);// Check if the size of the empty string container is 0
    CHECK(emptyStrContainer.empty());// Check if the empty string container is indeed empty
    CHECK_THROWS_AS(emptyStrContainer.removeElement("Hello"), std::invalid_argument);// Trying to remove an element from an empty container should throw an exception
    CHECK_THROWS_WITH(emptyStrContainer.removeElement("Hello"), "Element not found in the container");// Check if the exception message is correct
}
