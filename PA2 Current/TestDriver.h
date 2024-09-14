/** TestDriver.h
 * IMPORTANT: DO NOT EDIT THIS FILE MY COPY WILL BE USED FOR TESTING
**/

#ifndef PA2_PRIORITY_QUEUE_TESTDRIVER_H
#define PA2_PRIORITY_QUEUE_TESTDRIVER_H

// Declaration of functions used in TestDriver.cpp
bool compare_elements(Element &e1, Element &e2);
template <class T>
void test_constructors();
void test_insert_linked(PriorityQueue &p);
void test_insert_ordered(PriorityQueue &p);
void test_insert_heap(PriorityQueue &p);
void test_del_linked(PriorityQueue &p);
void test_del_heap(PriorityQueue &p);
void test_del_ordered(PriorityQueue &p);
void test_remove(PriorityQueue &p);
void test_size(PriorityQueue &p);
void test_peek(PriorityQueue &p);
void test_contains(PriorityQueue &p);
void test_clear_empty(PriorityQueue &p);
void test_full_size(PriorityQueue &p);
void test_PQLinkedList();
void test_PQOrdered();
void test_PQHeap();

#endif //PA2_PRIORITY_QUEUE_TESTDRIVER_H
