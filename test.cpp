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
