/* TestDriver.cpp CS210 SDSU
* Test driver file for RedBlackTree
*/
#include <iostream>
#include <memory>
#include "RedBlackTree.h"

// RedBlackTree testTree;
const int testInsertSet[11] = {12, 4, 23, 56, 15, 29, 1, 3, 6, 7, 30};
const int testViolationSet[4] = {3, 1, 5, 7};

void testAdd(RedBlackTree &testTree) {
   std::cout << ("------ TEST: add(int value) ------") << std::endl;
   try {
       // Add all the values in the testSet array
       std::cout << ("Inserting: ");
       for (auto i: testInsertSet) {
           std::cout << i << " ";
           testTree.add(i);
       }
       std::cout << "\n";
       std::cout << "Inserted all values into tree without crashing - Good" << std::endl;
       std::cout << "\n";

       // check that all those values were inserted
       std::cout << ("Contains: ");
       for (auto i: testInsertSet) {
           if (!testTree.contains(i)) {
               throw std::runtime_error("\nERROR: could not find value inside the tree");
           }
           std::cout << i << " ";
       }
       std::cout << "\n";
       std::cout << "Verified all values inserted are in the tree - Good"
                 << std::endl;
       std::cout << "\n";

       std::cout << "Performing some preliminary tests:" << std::endl;

       // preliminary checks without violation handling
       if ((testTree.get(30))->getValue() != 30) {
           throw std::runtime_error("ERROR: did not get correct Node");
       }
       if (testTree.get(7)->getValue() != 7) {
           throw std::runtime_error("ERROR: did not get correct Node");
       }
       if (testTree.get(1)->getValue() != 1) {
           throw std::runtime_error("ERROR: did not get correct Node");
       }

       std::cout << "Preliminary tests passed - Good" << std::endl;
       std::cout << "\n";
       std::cout << "Everything looks ok here" << std::endl;
   } catch (std::exception &e) {
       std::cout << e.what() << std::endl;
   }
}

void testRemove(RedBlackTree &testTree) {
   std::cout << "------ TEST: remove(int value) ------" << std::endl;
   try {
       // remove items
       std::cout << "Removing: " << std::endl;
       for (auto i: testInsertSet) {
           testTree.remove(i);
           std::cout << i << " ";
       }
       std::cout << "\n";
       std::cout << "Removed values from the tree without crashing - Good" << std::endl;

       // check to see if the values are still there
       std::cout << "Contains: ";
       for (auto i: testInsertSet) {
           if (testTree.contains(i))
               throw std::runtime_error("ERROR: found value that should be removed");
           std::cout << i << " ";
       }
       std::cout << "\n";
       std::cout << "Verified that the tree doesn't contain the values - Good" << std::endl;

       std::cout << "\n";
       std::cout << "Everything Looks ok here" << std::endl;
   } catch (std::exception &e) {
       std::cout << e.what() << std::endl;
   }
}

void testViolationHandlers(RedBlackTree &testTree) {
   std::cout << "------ TEST: testing for violation handling ------"
             << std::endl;
   try {
       // insert values into the tree
       for (auto i: testViolationSet) {
           testTree.add(i);
       }

       // by this point the tree should have made a color swap
       if (testTree.get(3)->getColor() != BLACK) {
        throw std::runtime_error("Error: root is not black");
       }
       if (testTree.get(3)->getLeftChild()->getColor() != BLACK){
           throw std::runtime_error("Error: the color should be black");
       }
       if (testTree.get(3)->getRightChild()->getColor() != BLACK){
           throw std::runtime_error("Error: the color should be black");
       }
       if (testTree.get(7)->getColor() != RED){
           throw std::runtime_error(
                   "Error: the color of the new Node should be red");
       }
       std::cout << "\n";
       std::cout << "Color Swap handled correctly when inserting 3,1,5,7";

       // This will force a right left rotation
       testTree.add(6);
       if (testTree.get(5)->getColor() != RED || testTree.get(7)->getColor() != RED) {
           throw std::runtime_error("Error: Node should be red after rotation and color swap");
       }
       if (testTree.get(6)->getColor() != BLACK) {
           throw std::runtime_error("Error: Node should be black after color swap");
       }

       std::cout << "\n";
       std::cout << "Left right rotation handled correctly after inserting 6";

       // this will cause color flip
       testTree.add(8);
       if (testTree.get(8)->getColor() != RED){
           throw std::runtime_error("Error: this inserted Node should be red");
       }
       if (testTree.get(8)->getParent()->getColor() != BLACK) {
           throw std::runtime_error("Error: the parent for this Node should be black");
       }
       if (testTree.get(8)->getParent()->getParent()->getColor() != RED) {
           throw std::runtime_error("Error: the grandparent for this Node should be red");
       }
       if (testTree.get(8)->getParent()->getParent()->getLeftChild()->getColor() != BLACK) {
           throw std::runtime_error("Error: the aunt aunt/uncle Node should be black");
       }

       std::cout << "\n";
       std::cout << "Color flip applied correctly after inserting 8";

       // this will cause a rotate left operation
       testTree.add(11);
       if (testTree.get(11)->getColor() != RED) {
           throw std::runtime_error("Error: the inserted Node should be red");
       }
       if (testTree.get(11)->getParent()->getColor() != BLACK) {
           throw std::runtime_error("Error: the parent for this Node should be black");
       }
       if (testTree.get(11)->getParent()->getLeftChild()->getColor() != RED) { 
           throw std::runtime_error("Error: the sibling for this Node should be RED");
       }

       std::cout << "\n";
       std::cout << "Rotate left performed correctly after inserting 11";

       // this will cause a color flip + a Left rotation. Keep in mind that the
       testTree.add(15);
       if (testTree.get(6)->getColor() != BLACK) {
           throw std::runtime_error("Error: the root Node should always be black");
       }
       if (testTree.get(3)->getColor() != RED || testTree.get(8)->getColor() != RED) {
           throw std::runtime_error("Error: don't forget to adjust colors after rotation");
       }
       if (testTree.get(6)->getLeftChild()->getValue() != 3) {
           throw std::runtime_error("Error: the left child of the root should be 3");
       }
       if (testTree.get(6)->getRightChild()->getValue() != 8) {
           throw std::runtime_error("Error: the right child of the root should be 8");
       }
       if (testTree.get(3)->getLeftChild()->getValue() != 1) {
           throw std::runtime_error("Error: left child should be 1 after operation");
       }
       if (testTree.get(3)->getRightChild()->getValue() != 5) {
           throw std::runtime_error("Error: right child should be 5 after operation");
       }

       std::cout << "\n";
       std::cout << "Color flip + left rotation applied correctly";

       testTree.remove(15);
       if (testTree.contains(15)) {
           throw std::runtime_error("Error: 15 should not exist in the tree");
       }

       std::cout << "\n";
       std::cout << "Deletion of a Node with no children applied correctly";

       testTree.remove(7);
       if (testTree.contains(7))
           throw std::runtime_error("Error: 7 should not exist in the tree");
       if (testTree.get(8)->getRightChild()->getValue() != 11)
           throw std::runtime_error("Error: the right child of 8 should be 11");
       if (testTree.get(6)->getColor() != BLACK)
           throw std::runtime_error("Error: the root should always be black");

       std::cout << "\n";
       std::cout << "Deletion of a black Node with no children applied correctly" << std::endl;

       testTree.remove(8);
       if (testTree.contains(8)) {
           throw std::runtime_error("Error: 8 should not exist in the tree");
       }
       if (testTree.get(6)->getRightChild()->getValue() != 11) {
           throw std::runtime_error("Error: the right child of the root Node should be 11");
       }
       if (testTree.get(11)->getParent()->getColor() == RED) {
           throw std::runtime_error("Error: The parent of 11 should be black, root is always black");
       }

       std::cout << "\n";
       std::cout << "Deletion of a Node with a child applied correctly" << std::endl;

       testTree.remove(3);
       if (testTree.contains(3)) {
           throw std::runtime_error("Error: 3 should not exist in the tree");
       }
       if (!testTree.contains(1) || !testTree.contains(5)) {
           throw std::runtime_error("Error: 1 and 5 should still be in the tree");
       }
       if (testTree.get(6)->getColor() != BLACK) {
           throw std::runtime_error("Error: the root is always black");
       }

       std::cout << "\n";
       std::cout << "Deletion of a Node with two children applied correctly";

       std::cout << "\n";
       std::cout << "Everything looks ok here";
   } catch (std::exception &e) {
        std::cout << e.what() << std::endl;
   }
}

int main() {
    RedBlackTree testTree;
    testAdd(testTree);
    testRemove(testTree);
    testViolationHandlers(testTree);
    return 0;
}