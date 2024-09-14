// PQOrdered.cpp
// Implement your Ordered Priority Queue in this file

/**
 *  PA2: Priority Queue
 *
 * For this assignment, you will write three implementations of a Priority Queue. For this
 * ADT, removal operations always return the object in the queue of highest priority, and if
 * multiple objects have the same priority, the one in the queue the longest shall be returned.
 * That is, no object of a given priority is ever removed as long as the queue contains one or
 * more object of a higher priority. Within a given priority FIFO order must be preserved. This
 * property is called stable sorting in a sorting algorithm, where two objects with equal keys
 * will need to appear in the same sorted order as they appear in the unsorted order.
 *
 *  CS210-5589 FALL2023
 * 10/27/2023
 *  @author Genesis Anne Villar
 * RED ID: 824435476
 */

#include "PriorityQueue.h"
#include "TestDriver.h"
#include <memory>
#include <string>
#include <utility>
#include <climits>
#include <algorithm>
using namespace std;

/* 
 * The implementations must have two constructors, a default constructor
 * with no arguments that uses the DEFAULT_MAX_CAPACITY constant from
 * PriorityQueue.h, and a constructor that takes a single integer parameter that represents the
 * maximum capacity of the priority queue
 * 
 * Class PriorityQueue contains function declarations that must be defined in the respective .cpp files. The PQUnordered, PQOrdered, and PQHeap 
public:

    // The maximum number of elements allowed in PriorityQueue
    int max_capacity;

    // pq contains a smart pointer to an array of type struct Element
    // pq is used for PQOrdered and PQHeap, pq is NOT used for PQLinkedList
    std::unique_ptr<Element[]> pq;

    // Pointer to head Node for PQLinkedList
    // Use Node *head for PQLinkedList, Node *head is NOT used for PQHeap or PQOrdered
    Node *head;
*/

static int current_size = 0;
// default constructor for Ordered List --> uses DEFAULT_MAX_CAPACITY
// does not implement Node *head

PriorityQueue::PriorityQueue() 
{
    max_capacity = DEFAULT_MAX_CAPACITY;
    current_size = 0;
    pq = make_unique<Element[]>(DEFAULT_MAX_CAPACITY);

}

PriorityQueue::PriorityQueue(int size) 
{
    max_capacity = size;
    current_size = 0;
    pq = make_unique<Element[]>(size);
}

// FUNCTIONS

/* 
    //  Inserts a new object into the priority queue.  Returns true if
    //  the insertion is successful.  If the PQ is full, the insertion
    //  is aborted, and the method returns false.
    bool insert(Element &element);

    //  The object of the highest priority must be the one returned by the
    //  remove() method; and if multiple objects have the same priority,
    //  the one in the queue the longest shall be returned, ie, FIFO
    //  return order must be preserved for objects of identical priority.
    //  Returns the default constructed Element if the PQ is empty.
    Element remove();

    //  Deletes all instances of the parameter from the PQ if found, and
    //  returns true.  Returns false if no match to the parameter obj is found.
    bool del(Element &element);

    //  Returns the object of highest priority in the PQ; if multiple
    //  objects have the same highest priority, return the one that has
    //  been in the PQ the longest, but does NOT remove it.
    //  Returns default constructed Element if the PQ is empty.
    Element peek();

    //  Returns true if the priority queue contains the specified element
    //  false otherwise.
    bool contains(Element &element);

    //  Returns the number of objects currently in the PQ.
    int size();

    //  Returns the PQ to its default state.
    void clear();

    //  Returns true if the PQ is empty, otherwise false.
    bool isEmpty();

    //  Returns true if the PQ is full, otherwise false.
    bool isFull();


*/


bool PriorityQueue::insert(Element& element)
{
    if (isFull())
    {
        return false;
    }

    pq[current_size] = element;
    current_size++;

    // Maintain ordering based on priority
    // We'll go from the end and swap until the order is maintained
    for (int i = current_size - 1; i > 0 && pq[i].priority > pq[i - 1].priority; i--)
    {
        swap(pq[i], pq[i - 1]);
    }

    return true;
}

// Remove the element with the highest priority and return it
Element PriorityQueue::remove()
{
    if (isEmpty())
    {
        return {};  // Return a default constructed Element
    }

    Element highestPriority = pq[0];
    for (int i = 1; i < current_size; i++)
    {
        pq[i - 1] = pq[i];
    }
    current_size--;

    return highestPriority;
}

// Delete the provided element
bool PriorityQueue::del(Element& element)
{
    int index = -1;
    for (int i = 0; i < current_size; i++)
    {
        if (pq[i].name == element.name &&
            pq[i].priority == element.priority &&
            pq[i].fifo == element.fifo)
        {
            index = i;
            break;
        }
    }

    if (index == -1)
        return false;  // Element not found

    for (int i = index; i < current_size - 1; i++)
    {
        pq[i] = pq[i + 1];
    }
    current_size--;

    return true;
}

// Peek at the highest priority without removing
Element PriorityQueue::peek()
{
    if (isEmpty())
    {
        return {};  // Return a default constructed Element
    }
    return pq[0];
}

// Check if the queue contains the provided element
bool PriorityQueue::contains(Element& element)
{
    for (int i = 0; i < current_size; i++)
    {
        if (pq[i].name == element.name &&
            pq[i].priority == element.priority &&
            pq[i].fifo == element.fifo)
        {
            return true;
        }
    }
    return false;
}

// Return the current size of the queue
int PriorityQueue::size()
{
    return current_size;
}

// Clear the queue
void PriorityQueue::clear()
{
    current_size = 0;
}

// Check if the queue is empty
bool PriorityQueue::isEmpty()
{
    return current_size == 0;
}

// Check if the queue is full
bool PriorityQueue::isFull()
{
    return current_size == max_capacity;
}


/* IMPORTANT: main() must be EXACTLY how it was provided
** provided to you when you submit your assignment.
**
** If you edit main for your own testing purposes,
** you MUST restore it to how it was provided to
** you before submission. 
*/
int main() {
    test_PQOrdered();
    return 0;
}