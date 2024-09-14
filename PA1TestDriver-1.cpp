
// PA1TestDriver.cpp

/**
 * This contains the test cases for the SortableArray.cpp file
 *
 * IMPORTANT!
 * DO NOT EDIT ANY OF THE FILE BELOW!
 */
 

#include "SortableArray.h"
#include <stdexcept>
#include <sys/stat.h>

// Test if add correctly adds an element
void test_add_element(SortableArray &x) {
    try {
        int unsorted_add[10] = {152, -32, 5, 0, 0, 5, 4, 3, 2, 19};
        for (int i = 0; i < 10; i++) {
            x.add(unsorted_add[i]);
        }
        int *object_arr = x.return_arr();
        for (int i = 0; i < 10; i++) {
            if (object_arr[i] != unsorted_add[i]) {
                throw std::runtime_error("ERROR: bool add(int element) Incorrectly adds elements");
            }
        }
        std::cout <<"SUCCESS: bool add(int element) Correctly adds elements" << std::endl;
    }
    catch (std::exception &e){
        std::cout << e.what() << std::endl;
    }
}

// Test if add correctly adds an element with index
void test_add_element_index(SortableArray& x) {
    try {
        int test_arr[5] = {0, 1, 2, 3, 5};
        x.add(1,0);
        x.add(3, 1);
        x.add(2, 1);
        x.add(5, 3);
        x.add(0, 0);
        int *arr = x.return_arr();

        for (int i = 0; i < 5; i++) {
            if (arr[i] != test_arr[i]) {
                throw std::runtime_error("ERROR: bool add(int element, int index) Incorrectly adds elements by index");
            }
        }
        std::cout << "SUCCESS: bool add(int element, int index) Correctly adds elements by index" << std::endl;
    }
    catch (std::exception &e){
        std::cout << e.what() << std::endl;
    }
}

// Tests if the get method returns the correct values
void test_get(SortableArray &x) {
    try {
        int correct_val = 5;
        int test_val = x.get(4);
        if (correct_val != test_val) {
            throw std::runtime_error("ERROR: int get(int index) Incorrectly gets value");
        } else {
            std::cout << "SUCCESS: int get(int index) Correctly gets value" << std::endl;
        }
    }
    catch (std::exception &e){
        std::cout << e.what() << std::endl;
    }

}

//Tests if remove correctly removes and returns values by index
void test_remove(SortableArray &x) {
    try {
        for (int i = 0; i < 10; i++) {
            x.remove(0);
        }

        x.add(25);
        int test_val = x.remove(0);
        if (test_val != 25){
            throw std::runtime_error("ERROR: int remove(int index) Incorrectly removes/returns values");
        }

        x.add(1);
        x.add(25);
        test_val = x.remove(1);
        if (test_val != 25){
            throw std::runtime_error("ERROR: int remove(int index) Incorrectly removes/returns values");
        }
        x.remove(0);

        std::cout << "SUCCESS: int remove(int index) Correctly removes/returns values" << std::endl;
    }
    catch (std::exception &e){
        std::cout << e.what() << std::endl;
    }
}

inline bool exists(const std::string &filename) {
    struct stat buffer = {};
    return (stat(filename.c_str(), &buffer) == 0);
}

// Tests if successfully saves file
void test_save(SortableArray &x) {
    try {
        std::string filename = "SortedNumberFile.txt";
        x.saveFile(filename);
        if (exists(filename)) {
            std::cout << "SUCCESS: bool saveFile(std::string fileName) Saves file" << std::endl;
//            remove(filename.c_str());
        } else {
            throw std::runtime_error("ERROR: bool saveFile(std::string fileName) Saved file not found");
        }
    }
    catch (std::exception &e){
        std::cout << e.what() << std::endl;
    }
}

// Tests if correctly reads and puts file into array
void test_read(SortableArray &x) {
    try {
        if (x.readFile("UnsortedNumberFile.txt")) {
            if (x.get(0) != 42175) {
                throw std::runtime_error("ERROR: bool readFile(std::string fileName) Incorrectly reads file");
            }
            if (x.get(999) != 43737) {
                throw std::runtime_error("ERROR: bool readFile(std::string fileName) Does not read entire file");
            }
        } else {
            throw std::runtime_error("ERROR: bool readFile(std::string fileName) Unable to read file");
        }
        std::cout << "SUCCESS: bool readFile(std::string fileName) Correctly reads file" << std::endl;
    }
    catch (std::exception &e){
        std::cout << e.what() << std::endl;
    }
}

// Tests if array correctly sorts
void test_insertion_sort(SortableArray &x) {
    try {
        x.insertionSort();
        if (x.get(0) != 56 || x.get(999) != 99892) {
            throw std::runtime_error("ERROR: void insertionSort() Does not correctly sort the file");
        } else {
            std::cout << "SUCCESS: void insertionSort() Correctly sorts the file" << std::endl;
        }
    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }

}

// Tests if size is correctly returned
void test_size(SortableArray &x) {
    try {
        int returned_val = x.size();
        if (returned_val != 10) {
            throw std::runtime_error("ERROR: int size() Incorrectly returned size");
        } else {
            std::cout << "SUCCESS: int size() Correctly returned size" << std::endl;
        }

    }
    catch (std::exception &e){
        std::cout << e.what() << std::endl;
    }
}


int main() {
    // Testing add, get, remove, and size methods
    std::cout << "-------TESTING SortableArray-------" << std::endl;
    SortableArray test1;
    test_add_element(test1);
    test_size(test1);
    test_remove(test1);
    test_add_element_index(test1);
    test_get(test1);

    // Testing read, save, and Insertion Sort methods
    SortableArray test2;
    test_read(test2);
    test_insertion_sort(test2);
    test_save(test2);

    return 0;
}