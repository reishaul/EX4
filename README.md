# Generic Container Including Iterators 

## Overview
This C++ project implements a generic MyContainer class that supports multiple operations on comparable types (defaulting to int). The container provides core functionalities such as:

Adding and removing elements

Accessing elements by index

Printing the container

Iterating with custom-defined orders

Additionally, it includes a collection of custom iterator types and a unit testing suite based on the doctest framework.

The container is designed to be simple, efficient, and fully testable.


## Iterators Types

AscendingOrder-  iterates from the smallest to the biggest element

DescendingOrder- iterates from the biggest to the smallest element

SideCrossOrder- Alternates between the smallest and largest, then second smallest/largest, and so on.

ReverseOrder-  iterates in reverse of insertion  order

Order- iterates in insertion order

MiddleOutOrder- Starts from the middle, then left and right alternately.

---
## Project Structure

### Directories and Files


├── Demo.cpp                   # Main demo file

├── tests.cpp                  # Unit tests using doctest

├── MyContainer.hpp            # Main container class

├── Iterators/                 # Folder containing iterator implementations

│   ├── OrderIterator.hpp

│   ├── SideCrossOrderIterator.hpp

│   ├── MiddleOutOrderIterator.hpp

│   └── ReverseOrderIterator.hpp

├── doctest.h                  # Header-only testing framework

├── Makefile                   # Makefile for compilation and execution

└── README.md                  # This file

---
## Building the Project

To compile the project:

```bash
make
```
This creates:


demo: a demo executable (optional).

tests: executable for unit testing.

Run the demo:
```bash
make Main
```
Running Tests

To build and run tests:
```bash
make test
```

To run memory checks with Valgrind:
```bash
make valgrind
```

Cleaning Build Files

To clean up all object files and executables:
```bash
make clean
```

## Requirements
g++ compiler with C++17 support

doctest.h (already included in the project)


## Usage Example -Descending Order
```bash
MyContainer<int> container;
container.addElement(7);
container.addElement(15);
container.addElement(6);
container.addElement(1);
container.addElement(2);

for (auto it = container.begin_descending_order(); it != container.end_descending_order(); ++it) {
        std::cout << *it << ' ';  
    }
std::cout << std::endl;
```

Expected output:
```bash
15 7 6 2 1
```


## Author

Developed by Rei Shaul

📧 reishaul1@gmail.com