//reishaul1@gmail.com
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include "MyContainer.hpp"

using namespace Rei;

TEST_CASE("MyContainer basic operations") {
    MyContainer<int> container;

    SUBCASE("Add elements") {
        container.addElement(10);
        container.addElement(20);
        container.addElement(30);
        CHECK(container.size() == 3);
    }

    SUBCASE("Remove elements") {
        container.addElement(10);
        container.addElement(20);
        container.removeElement(10);
        CHECK(container.size() == 1);
        CHECK_THROWS_AS(container.removeElement(100), std::invalid_argument);
        CHECK_THROWS_WITH(container.removeElement(100), "Element not found in the container");
    }

    SUBCASE("Check empty") {
        CHECK(container.empty());
        container.addElement(10);
        CHECK(!container.empty());
    }

    SUBCASE("Clear elements") {
        container.addElement(10);
        container.clear();
        CHECK(container.empty());
    }
    SUBCASE("Access elements") {
        container.addElement(10);
        container.addElement(20);
        CHECK(container[0] == 10);
        CHECK(container[1] == 20);
    }

    SUBCASE("Print elements") {
        container.addElement(10);
        container.addElement(20);
        std::ostringstream oss;
        container.print(oss);
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

    SUBCASE("Reverse order iterator") {
        auto it = container.begin_reverse_order();
        CHECK(*it == 50);
        ++it;
        CHECK(*it == 40);
        ++it;
        CHECK(*it == 30);
        ++it;
        CHECK(*it == 20);
        ++it;
        CHECK(*it == 10);
        ++it;
        CHECK(it == container.end_reverse_order());
    }

    SUBCASE("Side cross order iterator") {
        auto it = container.begin_side_cross_order();
        CHECK(*it == 10);
        ++it;
        CHECK(*it == 50);
        ++it;
        CHECK(*it == 20);
        ++it;
        CHECK(*it == 40);
        ++it;
        CHECK(*it == 30);
        ++it;
        CHECK(it == container.end_side_cross_order());
    }

    SUBCASE("Ascending order iterator") {
        auto it = container.begin_ascending_order();
        CHECK(*it == 10);
        ++it;
        CHECK(*it == 20);
        ++it;
        CHECK(*it == 30);
        ++it;
        CHECK(*it == 40);
        ++it;
        CHECK(*it == 50);
        ++it;
        CHECK(it == container.end_ascending_order());
    }

    SUBCASE("Descending order iterator") {
        auto it = container.begin_descending_order();
        CHECK(*it == 50);
        ++it;
        CHECK(*it == 40);
        ++it;
        CHECK(*it == 30);
        ++it;
        CHECK(*it == 20);
        ++it;
        CHECK(*it == 10);
        ++it;
        CHECK(it == container.end_descending_order());
    }
    SUBCASE("container that each element is a key and value pair"){
        struct numbers{
            std::string key;
            int value;
            bool operator<(const numbers& other) const {
                return value < other.value;
            }
            bool operator>(const numbers& other) const {
                return value > other.value;
            }
            bool operator==(const numbers& other) const {
                return value == other.value && key == other.key;
            }
        };
        MyContainer<numbers> KVContainer;
        KVContainer.addElement({"thirty", 30});
        KVContainer.addElement({"ten", 10});
        KVContainer.addElement({"forty", 40});
        KVContainer.addElement({"twenty", 20});
        KVContainer.addElement({"fifty", 50});

        auto it = KVContainer.begin_descending_order();
        CHECK(*it == numbers{"fifty", 50});
        ++it;
        CHECK(*it == numbers{"forty", 40});
        ++it;
        CHECK(*it == numbers{"thirty", 30});
        ++it;
        CHECK(*it == numbers{"twenty", 20});
        ++it;
        CHECK(*it == numbers{"ten", 10});
        ++it;
        CHECK(it == KVContainer.end_descending_order());

    }

    SUBCASE("Middle out order iterator") {
        auto it = container.begin_middle_out_order();
        CHECK(*it == 30);
        ++it;
        CHECK(*it == 20);
        ++it;
        CHECK(*it == 40);
        ++it;
        CHECK(*it == 10);
        ++it;
        CHECK(*it == 50);
        ++it;
        CHECK(it == container.end_middle_out_order());
    }

    SUBCASE("Order iterator") {
        auto it = container.begin_order();
        CHECK(*it == 10);
        ++it;
        CHECK(*it == 20);
        ++it;
        CHECK(*it == 30);
        ++it;
        CHECK(*it == 40);
        ++it;
        CHECK(*it == 50);
        ++it;
        CHECK(it == container.end_order());
    }
}

TEST_CASE("special cases"){
    MyContainer<int> container;


    SUBCASE("empty container"){
        auto it = container.begin();
        // for (; it != container.end(); ++it) {
        //     std::cout << *it << ' ';
        // }
        CHECK(it == container.end());
    }

    container.addElement(5);
    SUBCASE("container with one element"){
        auto it = container.begin_reverse_order();
        for (; it != container.end_reverse_order(); ++it) {
            //std::cout << *it << ' ';
        }
        CHECK(it==container.end_reverse_order());
    }

    MyContainer<> str;
    //str.addElement("abc");//cannot add string to int container
    str.addElement('r');
    str.addElement('e');
    str.addElement('i');

    SUBCASE("operator ->"){
        struct numbers{
            std::string key;
            int value;
            bool operator<(const numbers& other) const {
                return value < other.value;
            }
            bool operator>(const numbers& other) const {
                return value > other.value;
            }
            bool operator==(const numbers& other) const {
                return value == other.value && key == other.key;
            }
        };
        MyContainer<numbers> KVContainer;
        KVContainer.addElement({"thirty", 30});
        KVContainer.addElement({"ten", 10});
        KVContainer.addElement({"forty", 40});
        auto it = KVContainer.begin_reverse_order();

        CHECK(it->key == "forty");
        CHECK(it->value == 40);
        ++it;
        CHECK(it->key == "ten");
        CHECK(it->value == 10);
        ++it;
        CHECK(it->key == "thirty");
        CHECK(it->value == 30);
        ++it;
    }

    SUBCASE("operator *"){
        auto it = str.begin_middle_out_order();

        CHECK(*it=='e');
        ++it;
        CHECK(*it=='r');
        ++it;
        CHECK(*it=='i');
    }

    SUBCASE("operator ++"){
        auto it = str.begin_order();
        CHECK(*it=='r');
        ++it;
        CHECK(*it=='e');
        ++it;
        CHECK(*it=='i');

        // expected output: B
    }

    SUBCASE("post increment operator ++"){
        auto it = str.begin_order();
        CHECK(*it=='r');
        it++;
        CHECK(*it=='e');
        it++;
        CHECK(*it=='i');
        it++;
        CHECK(it==str.end_order());
    }


    SUBCASE("operator --"){
        auto it = str.begin_order();
        ++it;
        ++it;
        CHECK(*it=='i');
        --it;
        CHECK(*it=='e');
        --it;   
        CHECK(*it=='r');
        //--it; // This will throw an exception since it goes before the beginning
        CHECK_THROWS_AS(--it, std::out_of_range);
        CHECK_THROWS_WITH(--it, "Cannot decrement iterator before the beginning");

        // expected output: B
    }

    SUBCASE("INT AS A DEAFAULT&access overload[]"){
        MyContainer<> s;

        CHECK_NOTHROW(s.addElement('A'));
        CHECK_NOTHROW(s.addElement('B'));
        CHECK_NOTHROW(s.addElement(5));
        CHECK(s.size() == 3);
        CHECK(s[1]=='B');
        CHECK(s[2]==5);

        CHECK_NOTHROW(s.addElement(5.96));
        CHECK(s.size() == 4);
        CHECK(s[3]==5);

    }

    SUBCASE("operator == & != "){
        MyContainer<> str;
        str.addElement('a');
        str.addElement('B');
        str.addElement('c');
        str.addElement('d');
        auto it = str.begin_order();
        auto it2 = str.begin_order();
        CHECK(it==it2);
        ++it;
        CHECK(it!=it2);
        CHECK(it2!=str.end_order());
        ++it2;
        CHECK(it==it2);
        ++it2;
        CHECK(it!=it2);
        ++it2;
        CHECK(it!=it2);
        --it;
        ++it2;

        CHECK_THROWS_AS(++it2, std::out_of_range);
        CHECK_THROWS_WITH(++it2, "Iterator is out of range");


        MyContainer<int> c2;
        c2.addElement(1);
        c2.addElement(2);
        MyContainer<int> c3;
        c3.addElement(1);
        c3.addElement(3);

        auto it3 = c2.begin_order();
        auto it4 = c3.begin_order();

        //std::cout<<*it3<<std::endl;
        CHECK(*it3==*it4);
        ++it3;
        ++it4;
        CHECK(*it3!=*it4);

    }
}

TEST_CASE("Negative numbers cases"){
    MyContainer<int> container;
    container.addElement(-10);
    container.addElement(-20);
    container.addElement(-30);
    container.addElement(-40);
    container.addElement(-50);

    SUBCASE("Negative numbers in reverse order") {
        auto it = container.begin_reverse_order();
        CHECK(*it == -50);
        ++it;
        CHECK(*it == -40);
        ++it;
        CHECK(*it == -30);
        ++it;
        CHECK(*it == -20);
        ++it;
        CHECK(*it == -10);
        ++it;
        CHECK(it == container.end_reverse_order());
    }

    SUBCASE("Negative numbers in ascending order") {
        auto it = container.begin_ascending_order();
        CHECK(*it == -50);
        ++it;
        CHECK(*it == -40);
        ++it;
        CHECK(*it == -30);
        ++it;
        CHECK(*it == -20);
        ++it;
        CHECK(*it == -10);
        ++it;
        CHECK(it == container.end_ascending_order());
    }

    SUBCASE("Negative numbers in descending order") {
        auto it = container.begin_descending_order();
        CHECK(*it == -10);
        ++it;
        CHECK(*it == -20);
        ++it;
        CHECK(*it == -30);
        ++it;
        CHECK(*it == -40);
        ++it;
        CHECK(*it == -50);
        ++it;
        CHECK(it == container.end_descending_order());
    }

    SUBCASE("Negative numbers in side cross order") {
        auto it = container.begin_side_cross_order();
        CHECK(*it == -50);
        ++it;
        CHECK(*it == -10);
        ++it;
        CHECK(*it == -40);
        ++it;
        CHECK(*it == -20);
        ++it;
        CHECK(*it == -30);
        ++it;
        CHECK(it == container.end_side_cross_order());
    }
    SUBCASE("Negative numbers in middle out order") {
        auto it = container.begin_middle_out_order();
        CHECK(*it == -30);
        ++it;
        CHECK(*it == -20);
        ++it;
        CHECK(*it == -40);
        ++it;
        CHECK(*it == -10);
        ++it;
        CHECK(*it == -50);
        ++it;
        CHECK(it == container.end_middle_out_order());
    }
    SUBCASE("Negative numbers in order") {
        auto it = container.begin_order();
        CHECK(*it == -10);
        ++it;
        CHECK(*it == -20);
        ++it;
        CHECK(*it == -30);
        ++it;
        CHECK(*it == -40);
        ++it;
        CHECK(*it == -50);
        ++it;
        CHECK(it == container.end_order());
    }
}

// TEST_CASE()
