
/**
 *  PA1: Sortable Array
 *
 *
 * Implement the function prototypes provided in SortableArray.h (following). Your class should have
 * two constructors, a default constructor that uses DEFAULT_MAX_CAPACITY from the header
 * file and a constructor that takes a single integer as a parameter to define the maximum capacity
 * of the array. Additionally, your class should have a method of readFile() for reading the contents
 * of a file (UnsortedNumberFile.txt) and storing the values therein into the array. And then your
 * insertionSort() will sort the numbers in the Array. Afterwards the saveFile() method for storing the
 * contents of the array into the output file. This output file should be named SortedNumberFile.txt
 * and the format should be the same as the input file format (one entry per line).
 *
 *  CS210-5589 FALL2023
 *  9/30/2023
 *  @author Genesis Anne Villar
 * RED ID: 824435476
 */


#include "SortableArray.h"
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdexcept>
#define DEFAULT_TEST_SIZE 1024
using namespace std;


// NOTE: Methods should not accept indexes that are out of bounds

        // default constructor to automatically use default size for array
SortableArray::SortableArray()
{
    max_size = DEFAULT_TEST_SIZE;       //variable to store the size of the array --> uses default size value (1024)
    arr = new int[max_size];            // array
    count = 0;                          // store count the size of array
}

//explicit constructor that takes int size for array size
SortableArray::SortableArray(int size)
{
    max_size = size;                    //variable to store the size of the array --> uses given explicit value
    arr = new int[max_size];
    count = 0;
}

// Adds element to end of array if there is room
// Returns true if successful
bool SortableArray::add(int element)
{
    try
    {
        if (count < max_size)          //check if there is enough size to add element
        {
            arr[count++] = element;    //add desrired element and increment count
            return true;
        }
        else
        {
            throw std::out_of_range("Cannot add elements more than size allows");
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;        //I used his try/catch in PA1TestDriver lool
        return false;
    }
}

// Adds element at index and shift the array if needed
// Returns true if successful

bool SortableArray::add(int element, int index)
{
    try
    {
        //throws exception if... index is negative ... inputted index is greater or equal to size of array ... count is out of bounds of array
        if (index < 0 || index >= max_size || count >= max_size)
        {
            throw std::out_of_range("You are trying to add more elements than given size");
        }

        //insert at end and array is not full
        if (index == count && count < max_size)
        {
            arr[count++] = element;
            return true;
        }

        // shift following elements to the right
        for (int i = count; i > index; i--)
        {
            arr[i] = arr[i - 1];
        }

        //place new element at desired index
        arr[index] = element;
        count++;       //increment count
        return true;
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return false;

    }
}

// Returns the element at a given index
int SortableArray::get(int index)
{
    try
    {

        if (index >= 0 && index < count)     //checks if valid index is valid within the array 
        {
            return arr[index];
        }

        else
        {
            throw std::out_of_range("Index:" + std::to_string(index) + " is out of bounds");
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return -1;       //error value to indicate issue
    }
}

// Removes and returns element at given index
// Array should be shifted after removal of element
int SortableArray::remove(int index)
{
    try
    {
        if (index < 0 || index >= count)
        {
            throw std::out_of_range("Index:" + std::to_string(index) + " is out of bounds");
        }
        else
        {
            int removedElement = arr[index];       //store value of the element to be removed

            //shift elements to the left to fill the gap from removed element
            for (int i = index; i < count - 1; i++)
            {
                arr[i] = arr[i + 1];
            }
            count--; //decrease count
            return removedElement;
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return -1;       //error value to indicate issue
    }
}

// Returns the size/capacity of the array
int SortableArray::size() const
{
    return max_size;   //returns current number of stored elements
}


// Reads file from given fileName and stores each number into the array
// Returns true if successful
bool SortableArray::readFile(std::string fileName)
{
    try
    {
        std::ifstream inFile(fileName);      //input stream
        std::string line;

        //check if inFile was properly opened
        if (!inFile.is_open())
        {
            throw std::runtime_error("file unable to be opened");
        }

        //read inFile line by line
        while (getline(inFile, line))
        {
            std::istringstream inputString(line);     // operate on input line
            int value;
            inputString >> value;                    // convert line to an int
            add(value);                              // add int to the array
        }

        inFile.close();
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return false;
    }
}




// Saves the current array into a text file
// Returns true if successful
bool SortableArray::saveFile(std::string fileName)
{
    try
    {
        std::ofstream outFile(fileName);        //output stream

        //check if outFile was properly opened
        if (!outFile.is_open())
        {
            throw std::runtime_error("file unable to be opened");
        }

        //write each element of the array to the outfile
        for (int i = 0; i < size(); i++)
        {
            outFile << arr[i] << "\n";        //format same as input file(one entry per line)
        }

        outFile.close();
        return true;
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return false;
    }
}

// Sorts the current array with insertion sort in place algorithim
//O(N^2) time complexity....
void SortableArray::insertionSort()
{
    try
    {
        for (int i = 1; i < count; i++)
        {
            int put = arr[i];       //this is the element we are trying to sort in place correctly
            int j = i - 1;

            //shift elements to the right until we find the correct index
            while (j >= 0 && arr[j] > put)
            {
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = put;       //place new element
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
}

