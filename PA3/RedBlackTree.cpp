/* RedBlackTree.cpp
* Source file for RedBlackTree
*/

/**
 *  PA3: Red-Black Tree -- RedBlackTree.cpp
 *
 * For this assignment you will implement a red-black tree.
 *
 *
 * A red-black tree is a binary search tree with nodes colored red and black in a way that satisfies the following properties:
 *  --- Root Property: The root is black.
 *  --- External Property: Every external node is black.
 *  --- Red Property: The children of a red node are black.
 *  --- Depth Property: All external nodes (leaves) have the same black depth, defined as the number of proper ancestors that are black.
 *
 * For the Red-Black tree class, you will implement four methods: add, remove, contains, and get.
 * The first two methods modify the tree and might trigger rotations. The third method checks if the
 * tree contains a value. The last method searches for a value within the tree and returns the node
 * containing it.
 *
 *  CS210-5589 FALL2023
 *  12/4/2023
 *  @author Genesis Anne Villar
 *  RED ID: 824435476
 */


// !! NOTE: Each method must be as efficient as possible. That is, a O(n) is unacceptable if the method could be written with O(log n) complexity. !!

#include "RedBlackTree.h"
#include <type_traits>
#include <algorithm>
#include <iostream>
using namespace std;


/* HELPER METHODS IN RedBlackTree.h

    void leftRotate(Node* x);
    void rightRotate(Node* x);
    void fixRedRed(Node* x);
    void fixBlackBlack(Node* x);
    void transplant(Node* x, Node* y);
    Node* minimum(Node *node);
    Node* searchTree(int value);
    Node* getSibling(Node* x);

*/

// helper method for LEFT rotation around node x while maintain the red-black tree balance
void RedBlackTree::leftRotate(Node* x)
{
    try
    {
        // conditions for left rotation:
        // 1.) x != nullptr 
        // 2.) x should have a RIGHT child
        
        // check if x is nullptr or x's right child is nullptr
        if (x == nullptr || x->right == nullptr)
        {
            // if either error case is true ... left rotation is not possible
            throw std::invalid_argument("left rotation cannot occur");
            return; 
        }

        Node* y = x->right; // node y will become new parent of subtree after rotation
                            
        x->right = y->left; // turn y's left subtree into x's right subtree (maintain binary search tree property)
        
        if (y->left != nullptr)
        {
            y->left->parent = x; //corrects parent-child relationship after changing x's right child
        }

        y->parent = x->parent; // link x's parent to y

        // 3 cases are possible for x's parent
        if (x->parent == nullptr) // 1.) x is the root
        {
            this->root = y; // after rotation, y becomes the new root
        }
        else if (x == x->parent->left) // 2.) x is the left child of its parent 
        {
            x->parent->left = y; // y takes x's place as the left child
        }
        else
        {
            x->parent->right = y; // 3.) x is the right child of its parent .... y takes x's place as the right child
        }

        y->left = x; // complete rotation... x becomes left child of y 
        x->parent = y;
    }
    catch(const std::invalid_argument& e) // handle cases were rotation are invalid (nullptr or missing child nodes)
    {
        std::cout << "(left rotate) error with: " << e.what() << std::endl;
    }
}

// helper method for RIGHT rotation around node x while maintain the red-black tree balance
void RedBlackTree::rightRotate(Node* x)
{
    try
    {
        // conditions for right rotation:
        // 1.) x != nullptr 
        // 2.) x should have a LEFT child

        // check if x is nullptr or x's left child is nullptr
        if (x == nullptr || x->left == nullptr)
        {
            // if either error case is true ... right rotation is not possible
            throw std::invalid_argument("right rotation cannot occur");
            return;
        }

        Node* y = x->left; // node y will become the new parent of the subtree after rotation

        x->left = y->right; // turn y's right subtree into x's left subtree (maintain binary search tree property)

        if (y->right != nullptr)
        {
            y->right->parent = x; // corrects parent-child relationship after changing x's left child
        }

        y->parent = x->parent; // link x's parent to y

        // 3 cases are possible for x's parent
        if (x->parent == nullptr) // 1.) x is the root
        {
            this->root = y;
        }
        else if (x == x->parent->right) // 2.) x is the right child of its parent
        {
            x->parent->right = y; // y takes x's place as the right child
        }
        else // 3.) x is the left child of its parent
        {
            x->parent->left = y; // y takes x's place as the left child
        }

        y->right = x; // complete rotation... x becomes right child of y 
        x->parent = y;
    }
    catch (const std::invalid_argument& e) // handle cases were rotation are invalid (nullptr or missing child nodes)
    {
        std::cout << "(right rotate) error with: " << e.what() << std::endl;
    }
}


// helper method that returns the sibling of a given node in the tree
// helps with add + remove method since helps maintain properties of red-black tree 
//              ---> color and position of a node's sibling can affect the necessary tree restructuring and recoloring
Node* RedBlackTree::getSibling(Node* x) 
{
    try
    {
        // check if x is null or the root has no sibling.. if so return nullptr
        if (x == nullptr || x->parent == nullptr)
        {
            return nullptr;
        }

        // check if x is a left or right child of its parent
        if (x == x->parent->left)
        {
            // if x == left child ... sibling == right child
            return x->parent->right;
        }
        else
        {
            // if x == right child ... sibling == left child
            return x->parent->left;
        }
    }
    catch (const std::exception& e) // catch and handle standard exceptions
    {
        std::cout << "(getSibling) error with: " << e.what() << std::endl;
    }
}

// helper method that fixes red-red violation (for add method)
//   ----> performs rotations or recoloring if necessary
void RedBlackTree::fixRedRed(Node* x)
{
    try
    {
        if (x == root) // first.. check if x is root of the tree
        {
            x->color = BLACK; // if so, recolor it to black (root property)
            return;
        }

        // define necessary nodes
        Node* parent = x->parent;
        Node* grandparent = parent->parent;
        Node* uncle = nullptr;

        // check if the parent is red ... indicating a red-red violation
        if (parent->color != BLACK)
        {
            if (grandparent->left == parent)    // determine uncle node
            {
                uncle = grandparent->right;
            }
            else
            {
                uncle = grandparent->left;
            }

            // case 1 : uncle is red  ... recolor the nodes 
            if (uncle != nullptr && uncle->color == RED)
            {
                // perform color flip  -- parent & uncle = black , grandparent = red
                // resolves red-red violation
                parent->color = BLACK;
                uncle->color = BLACK;
                grandparent->color = RED;

                fixRedRed(grandparent); // recursively to fix red-red violation for grandparent change
            }

            else
            {
                // case 2: uncle is black ... perform rotations and recolor
                if (parent == grandparent->left)
                {
                    if (x == parent->left)
                    {
                        // Left-left case (single rotation need)
                        swap(parent->color, grandparent->color);
                        rightRotate(grandparent);
                    }

                    else
                    {
                        // Left-right case (double rotation need)
                        // LEFT rotate parent, then RIGHT rotate grandparent
                        leftRotate(parent);
                        swap(x->color, grandparent->color);
                        rightRotate(grandparent);
                    }
                }

                else
                {
                    if (x == parent->right)
                    {
                        // Right-right case (single rotation need)
                        swap(parent->color, grandparent->color);
                        leftRotate(grandparent);
                    }

                    else
                    {
                        // Right-left case (double rotation need)
                        // RIGHT rotate parent, then LEFT rotate grandparent
                        rightRotate(parent);
                        swap(x->color, grandparent->color);
                        leftRotate(grandparent);
                    }
                }
            }
        }
    }
    catch (const std::exception& e) // catch and handle standard exceptions
    {
        std::cout << "(fixRedRed) error with: " << e.what() << std::endl;
    }
}


// helper method that fixes black-black violation (for remove method)
// maintains black depth property of the tree 
//    ---> peforms recoloring and rotations to balance black heights
void RedBlackTree::fixBlackBlack(Node* x)
{
    try
    {
        // check for null pointer issues or there is nothing left to fix (x = root)
        if (x == nullptr || x == root)
        {
            return; 
        }

        // define necessary nodes
        Node* sibling = getSibling(x);
        Node* parent = x->parent;

        // case 1: no sibling ... propagate the black-black violation up to the parent
        if (sibling == nullptr)
        {
            fixBlackBlack(parent);
        }

        else
        {
            // case 2: sibling is red ...perform rotations and recolor
            if (sibling->color == RED)
            {
                // convert to a black sibling case
                parent->color = RED;
                sibling->color = BLACK;

                // determine rotation direction 
                if (sibling == parent->left) // if sibling is left, right rotate parent 
                {
                    rightRotate(parent);
                }
                else
                {
                    leftRotate(parent); // if sibling is right, left rotate parent 
                }

                fixBlackBlack(x); // re-check for black-black violation at x
            }
            else
            {
                // case 3: sibling black
                // perform different rotations based on red child and sibling position
                if ((sibling->left != nullptr && sibling->left->color == RED) || (sibling->right != nullptr && sibling->right->color == RED))
                {
                    // At least one red child
                    // perform different rotations on specific configurations
                    if (sibling->left != nullptr && sibling->left->color == RED)
                    {
                        if (sibling == parent->left)
                        {
                            // Left-left case (single rotation w/ recolor)
                            sibling->left->color = sibling->color;
                            sibling->color = parent->color;
                            rightRotate(parent);
                        }

                        else
                        {
                            // right-left case (double rotation w/ recolor)
                            // RIGHT rotate sibling, then LEFT rotate parent
                            sibling->left->color = parent->color;
                            rightRotate(sibling);
                            leftRotate(parent);
                        }
                    }
                    else
                    {
                        if (sibling == parent->right)
                        {
                            // right-right case (single rotation w/ recolor)
                            sibling->right->color = sibling->color;
                            sibling->color = parent->color;
                            leftRotate(parent);
                        }
                        else
                        {
                            // left-right case (double rotation w/ recolor)
                            // LEFT rotate sibling, then RIGHT rotate parent
                            sibling->right->color = parent->color;
                            leftRotate(sibling);
                            rightRotate(parent);
                        }
                    }
                    parent->color = BLACK; //after rotation, parent is colored black
                }
                else
                {
                    // case 4: sibling is black with two black children
                    sibling->color = RED; // recolor the sibling to red to balance the black heights
                    
                    if (parent->color == BLACK) // if parent is black, black-black violation moves up the tree
                    {
                        fixBlackBlack(parent);
                    }
                    else
                    {
                        parent->color = BLACK; //if parent is red, recolor to black
                    }
                }
            }
        }
    }
    catch (const std::exception& e) // catch and handle standard exceptions
    {
        std::cout << "(fixBlackBlack) error with: " << e.what() << std::endl;
    }
}

// helper method that replaces one subtree (node x) as a child of its parent with another subtree (node y)
// used in remove method to handle the replacement of subtrees and updates parent pointers
//          -----> ensure the tree's integrity is maintained after a node is removed
void RedBlackTree::transplant(Node* x, Node* y) 
{
    try
    {
        if (x->parent == nullptr) // check if node u is root of tree
        {
            root = y; // if so, set root of tree to v
        }
        else if (x == x->parent->left) // check if u is the LEFT child of its parent
        {
            x->parent->left = y; // if so, replace the left child to v
        }
        else
        {
            x->parent->right = y; // if u is the RIGHT child of its parent, replace right child to v
        }

        // update so that v parent pointer is now to u's parent
        if (y != nullptr)
        {
            y->parent = x->parent;
        }
    }
    catch (const std::exception& e) // catch and handle standard exceptions
    {
        std::cout << "(transplant) error with: " << e.what() << std::endl;
    }
}


// helper method that finds the node with the minimum value in a given subtree
// used in remove method in order to help find the sucessor of a node
Node* RedBlackTree::minimum(Node* node) 
{
    try
    {
        while (node->left != nullptr) // start at given node and move down the left side of tree
        {
            node = node->left; // keep traversing left until the leftmost node is reached
        }
        return node; // leftmost node == smallest value in subtree
    }
    catch (const std::exception& e) // catch and handle standard exceptions
    {
        std::cout << "(minimum) error with: " << e.what() << std::endl;
    }
}


// helper method that uses while loop to check if a value exists in the tree
// ---> implements a simple binary search ... moving left or right depending on the value compared
Node* RedBlackTree::searchTree(int value) 
{
    try
    {
        Node* temp = root; //temp == current node

        // loop until temp is nullptr ... will mean the end of tree is reached
        while (temp != nullptr)
        {
            if (value < temp->val)  // if given int value is LESS than temp node's value... go left
            {
                temp = temp->left;
            }
            else if (value > temp->val) // if given int value is GREATER than temp node's value... go left
            {
                temp = temp->right;
            }
            else
            {
                return temp; // return value if found
            }
        }
        return nullptr; // return nullptr if not found
    }
    catch (const std::exception& e) // catch and handle standard exceptions
    {
        std::cout << "(searchTree) error with: " << e.what() << std::endl;
    }
}

/** METHODS TO IMPLEMENT in RedBlackTree.h
*
   // Default constructor for RedBlackTree
    RedBlackTree();

    //Inserts a value into the tree and performs the necessary balancing
     !! NOTE: For the add operation, you need to remedy a potential double red violation !!
    void add(int value);

    //Removes a value from the tree if present and performs the necessary balancing
     !! NOTE: For the remove operation, you need to remedy a potential double black violation. !!
    void remove(int value);

    //Returns true if the tree contains the specified value
    bool contains(int value);

    //Returns Node containing specified value
    Node* get(int value);

*/

// Default constructor for RedBlackTree
RedBlackTree::RedBlackTree()
{
	root = nullptr; // initialize w/ empty tree (nullptr)
}


// This method inserts a new node into the tree 
//  !! NOTE: For the add operation, you need to remedy a potential double red violation !!
// 
// performs a standard binary search tree (BST) insert
// helper method fixRedRed is called to fix any violations of Red-Black properties that may occur
void RedBlackTree::add(int value)
{
    try
    {
        Node* newNode = new Node(value); // create new node with given value

        // BST insert
        // case 1: if tree is empty, insert new node as root and color = black
        if (root == nullptr)
        {
            newNode->color = BLACK;
            root = newNode;
        }
        else
        {
            // case 2 : if tree NOT empty, find correct position for new node
            Node* temp = root; // temp for current node

            while (temp != nullptr) // traverse tree to find correct position
            {
                if (newNode->val < temp->val) // if new value is less than current node's value ... go LEFT
                {
                    if (temp->left == nullptr)
                    {
                        temp->left = newNode; // if left child is null, place new node here
                        newNode->parent = temp;
                        break;
                    }
                    else
                    {
                        temp = temp->left;  // if left child is occupied, move to the left child
                    }
                }

                else  // if new value is greater than or equal to current node's value ... go RIGHT
                {

                    if (temp->right == nullptr)
                    {
                        temp->right = newNode;  // if right child is null, place new node here
                        newNode->parent = temp;
                        break;
                    }
                    else
                    {
                        temp = temp->right; // if right child is occupied, move to the right child
                    }
                }
            }
            // NOW WORKS !! fixed left rotate and right rotate
            fixRedRed(newNode); // check and fix red red voilaton if exists
        }
    }
    catch(const std::bad_alloc& e) // catch memory allocation errors relating to adding elements
    {
        std::cout << "Error has occured in add(int value) method with memory allocation: " << e.what() << std::endl;
    }
    catch (std::exception& e) // catch and handle standard exceptions
    {
        std::cout << "Error has occured in add(int value) method with exception: " << e.what() << std::endl;
    }
}

//Removes a value from the tree if present and performs the necessary balancing
// !! NOTE: For the remove operation, you need to remedy a potential double black violation. !!
//
// helper method fixBlackBlack is called to fix any violations of Red-Black properties that may occur
void RedBlackTree::remove(int value)
{
    try
    {
        Node* nodeToDelete = searchTree(value); // use helper method to find node that has the value that needs to be deleted
       
        if (nodeToDelete == nullptr)    //check for nullptr issues
        {
            return; // value not found in tree
        }

        // define necessary nodes
        Node* y = nodeToDelete; // y -- will either be the node to delete or node to replace the deleted node
        Node* x = nullptr; // x -- will be the child of the deleted or replaced node
        int yOriginalColor = y->color;

        // case 1: nodeToDelete has no left child
        if (nodeToDelete->left == nullptr)
        {
            // set node x as right child of nodeToDelete
            x = nodeToDelete->right;
            transplant(nodeToDelete, nodeToDelete->right); // replace nodeToDelete with its right child
        }

        // case 2: nodeToDelete has no right child
        else if (nodeToDelete->right == nullptr)
        {
            x = nodeToDelete->left; // x is the left child
            transplant(nodeToDelete, nodeToDelete->left); // replace nodeToDelete with its left child
        }

        // case 3: node to delete has two children
        else
        {
            y = minimum(nodeToDelete->right); // find successor of nodeToDelete using minimum helper method
            yOriginalColor = y->color; // update orginal color to sucessor's
            x = y->right; // x is the right child of sucessor

            if (y->parent == nodeToDelete) // if x is not nullptr...
            {
                if (x) x->parent = y; // update x's parent to y 
            }
            else   // if the successor is not the direct child of the node to delete...
            {
                transplant(y, y->right); // replace the successor with its right child
                y->right = nodeToDelete->right; // then move the successor to the place of nodeToDelete
                y->right->parent = y;
            }

            transplant(nodeToDelete, y); // replace nodeToDelete with its successor y
            y->left = nodeToDelete->left;
            y->left->parent = y;
            y->color = nodeToDelete->color;
        }

        delete nodeToDelete; // now delete the node


        if (yOriginalColor == BLACK) // check nodeToDelete's orginal color and fix potential double black violations
        {
            fixBlackBlack(x);
        }
    }
    catch(std::exception & e) // catch and handle standard exceptions
    {
        std::cout << "Error has occured in add(int value) method with exception: " << e.what() << std::endl;
    }
}

// Returns true if the tree contains the specified value
bool RedBlackTree::contains(int value) 
{
    try
    {
        return searchTree(value) != nullptr; // uses searchTree helper method to find
                                            // if given value is found, return TRUE ... else nullptr was found and return FALSE
    }
    catch (std::exception& e) // catch and handle standard exceptions
    {
        std::cout << "Error has occured in contains(int value) method" << e.what() << std::endl;
        return false;
    }
}


// Returns Node containing specified value
Node* RedBlackTree::get(int value) 
{
    try 
    {
        return searchTree(value); // uses searchTree helper method to find AND return node
                                  // if given value is found, return value... else nullptr is returned
    }
    catch (std::exception& e) // catch and handle standard exceptions
    {
        std::cout << "Error has occured in get(int value) method" << e.what() << std::endl;
        return nullptr;
    }
}