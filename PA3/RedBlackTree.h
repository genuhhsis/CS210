/* RedBlackTree.h CS210 SDSU
* Header file for RedBlackTree
* You may add to this file as needed.
*/

/**
 *  PA3: Red-Black Tree -- RedBlackTree.h
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

#ifndef REDBLACKTREE
#define REDBLACKTREE

// Defines BLACK = 0, RED = 1
enum COLOR {BLACK, RED};

// Node class 
// Contains already defined methods
// You may add helper methods if needed
class Node {
public:
    int val;
    int color;
    Node *parent;
    Node *left;
    Node *right;

    Node(int val) : val(val) 
    {
	    parent = left = right = nullptr;
	    color = RED;
    }

    int getColor() 
    { 
        return color; 
    }

    Node* getLeftChild() 
    { 
        return left; 
    }
    
    Node* getRightChild() 
    { 
        return right; 
    }
    
    Node* getParent() 
    { 
        return parent; 
    }
    int getValue() 
    { 
        return val; 
    };

};

// RedBlackTree class
class RedBlackTree {
private:
    Node* root;

public:
    // You must implement the following five methods

    // Default constructor for RedBlackTree
    RedBlackTree();

    //Inserts a value into the tree and performs the necessary balancing
    void add(int value);

    //Removes a value from the tree if present and performs the necessary balancing
    void remove(int value);

    //Returns true if the tree contains the specified value
    bool contains(int value);

    //Returns Node containing specified value
    Node* get(int value);


    // SUGGESTED GIVEN HELPER METHODS
    // You may remove these methods or add more if needed

    void leftRotate(Node* x);
    void rightRotate(Node* x);
    void fixRedRed(Node* x);
    void fixBlackBlack(Node* x);
    
    // MY OWN HELPER METHODS

    // replaces one subtree as a child of its parent with another subtree
    void transplant(Node* x, Node* y);

    // finds the node with the minimum value in a given subtree
    Node* minimum(Node *node);

    // check if a value exists in the tree
    Node* searchTree(int value);
    
    // returns the sibling of a given node in the tree
    Node* getSibling(Node* x);
};

#endif // REDBLACKTREE