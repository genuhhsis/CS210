// SortableArray.h

/**
 * This contains the class declarations for a SortableArray
 * These are the declarations of the methods you will define in SortableArray.cpp
 *
 * IMPORTANT!
 * DO NOT EDIT ANY OF THE FILE BELOW!
 */

#include <iostream>
#include <fstream>

#ifndef SORTABLE_ARRAY_H
#define SORTABLE_ARRAY_H

#define DEFAULT_TEST_SIZE 1024

class SortableArray {
    // Instance variable to store array in
    int *arr;

    // Instance variable to store the current count of the array
    int count;

    // Instance variable to store the size of the array
    int max_size;

public:
    // Implement these 10 method prototypes
    // Methods should not accept indexes that are out of bounds

    // Default constructor
    SortableArray();

    // Constructor that takes int size as input
    explicit SortableArray(int size);

    // Adds element to end of array if there is room
    // Returns true if successful
    bool add(int element);

    // Adds element at index and shift the array if needed
    // Returns true if successful
    bool add(int element, int index);

    // Returns the element at a given index
    int get(int index);

    // Removes and returns element at given index
    // Array should be shifted after removal of element
    int remove(int index);

    // Returns the size/capacity of the array
    int size() const;

    // Reads file from given fileName and stores each number into the array
    // Returns true if successful
    bool readFile(std::string fileName);

    // Saves the current array into a text file
    // Returns true if successful
    bool saveFile(std::string fileName);

    // Sorts the current array with insertion sort in place
    void insertionSort();


    // Used for testing purposes
    int* return_arr(){
        return arr;
    };

    // DESTRUCTOR - DO NOT DEFINE
    // Destructor for dynamically allocated arr[] using new
    // Do not use malloc
    ~SortableArray() {
        delete[] arr;
    }

};


#endif //SORTABLE_ARRAY_H
