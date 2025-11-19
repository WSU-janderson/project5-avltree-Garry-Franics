/*-------------------------------------------------------------------------------------------
* Name: Garry Francis
* Project: AVLTree
*
* This is the cpp file for the AVLTree and AVLNode classes. It contains all the constructor
* and function definitions. This file includes definitions for: the AVLTree constructor, the
* AVLTree copy constructor, the AVLTree deconstructor, the insert function, the contains
* function, the get function, the findRange function, the keys function, the size function,
* the operator [], =, and << override functions, the getHeight(tree) function, the AVLNode
* constructor, the numChildren function, the isLeaf function, the getHeight(node) function,
* the remove function, the balanceNode function, and any recursive functions that are called
* by functions previously listed.
* -----------------------------------------------------------------------------------------*/

#include "AVLTree.h"
#include <string>
#include <optional>
#include <vector>

using namespace std;

//AVLTree constructor
AVLTree::AVLTree() {
    //Initialize class variables
    balance = 0;
    num = 0;
    root = nullptr;
}

//AVLTree copy constructor
AVLTree::AVLTree(const AVLTree& other) {
    //Copy over class variables
    this->balance = other.balance;
    this->num = other.num;
    //Except root we need that null
    this->root = nullptr;
    //Enter the recursion
    copyConstructorRecursion(this->root, other.root);
}
void AVLTree::copyConstructorRecursion(AVLNode*& current, const AVLNode* other) {
    //Stop if a nullptr is hit
    if (other == nullptr) {
        current = nullptr;
        return;
    }
    //Make a new node copying key and value
    current = new AVLNode(other->key, other->value);
    //Copy node height value
    current->height = other->height;
    //Move to the left node
    copyConstructorRecursion(current->left, other->left);
    //Move to the right node
    copyConstructorRecursion(current->right, other->right);
}

//AVLTree deconstructor
AVLTree::~AVLTree() {
    //Begin recursion
    deconstructorRecursion(root);
    root = nullptr;
    num = 0;
    balance = 0;
}
void AVLTree::deconstructorRecursion(AVLNode*& current) {
    //Stop if a nullptr is hit
    if (current == nullptr) {
        return;
    }
    //Move to the left node
    deconstructorRecursion(current->left);
    //Move to the right node
    deconstructorRecursion(current->right);
    //Delete the nodes as functions get returned
    delete current;
    //Set nullptr
    current = nullptr;
}

//Insert
bool AVLTree::insert(const string& key, const size_t value) {
    //Begin recursion
    return insert(root, key, value);
}
bool AVLTree::insert(AVLNode*& current, const string& key, const size_t& value) {
    //If nullptr add the new node
    if (current == nullptr) {
        current = new AVLNode (key, value);
        //Increase size tracker by 1
        num++;
        return true;
    }
    //If node is already in the tree do not add a duplicate
    if (contains(current, key)) {
        return false;
    }
    //Make a boolean to return
    bool inserted = false;
    //If the key is less than current key move left
    if (key < current->key) {
        inserted = insert(current->left, key, value);
    }
    //If the key is greater than current key move right
    else if (key > current->key) {
        inserted = insert(current->right, key, value);
    }
    //Return
    return inserted;
}

//Contains
bool AVLTree::contains(const string& key) {
    //Begin recursion
    return contains(root, key);
}
bool AVLTree::contains(AVLNode*& current, const string& key) const {
    //If nullptr is hit the key is not in the tree
    if (current == nullptr) {
        return false;
    }
    //If the key is found the key is in the tree
    if (current->key == key) {
        return true;
    }
    //Make a boolean to return
    bool contained = false;
    //If the key is less than current key move left
    if (key < current->key) {
        contained = contains(current->left, key);
    }
    //If the key is greater than current key move right
    else if (key > current->key) {
        contained = contains(current->right, key);
    }
    //Return
    return contained;
}

//Get
optional<size_t> AVLTree::get(const string& key) {
    //Begin recursion
    return get(root, key);
}
optional<size_t> AVLTree::get(AVLNode*& current, const string& key) const {
    //Make an optional size_t to return
    optional<size_t> gotten{};
    //If the key is not in the tree there is no value to return
    if (!contains(current, key)) {
        return nullopt;
    }
    //If it is the key return the value
    if (current->key == key) {
        gotten = current->value;
        return gotten;
    }
    //If the key is less than current key move left
    if (key < current->key) {
        gotten = get(current->left, key);
    }
    //If the key is greater than current key move right
    else if (key > current->key) {
        gotten = get(current->right, key);
    }
    //Return
    return gotten;
}

//findRange
vector<string> AVLTree::findRange(const string& lowKey, const string& highKey) {
    //Clear range vector for new call
    range.clear();
    //Begin recursion
    findRange(root, lowKey, highKey);
    //Return range
    return range;
}
void AVLTree::findRange(AVLNode*& current, const string& lowKey, const string& highKey) {
    //If nullptr is hit stop
    if (current == nullptr) {
        return;
    }
    //If current key is in the desired range add it to the vector
    if (current->key <= lowKey && current->key >= highKey) {
        range.push_back(current->key);
    }
    //Move to the left node
    findRange(current->left, lowKey, highKey);
    //Move to the right node
    findRange(current->right, lowKey, highKey);
}

//Keys
vector<string> AVLTree::keys() {
    //Clear range vector for new call
    range.clear();
    //Begin recursion
    keys(root);
    //Return range
    return range;
}
void AVLTree::keys(AVLNode*& current) {
    //If nullptr is hit stop
    if (current == nullptr) {
        return;
    }
    //Add current key to the vector
    range.push_back(current->key);
    //Move to the left node
    keys(current->left);
    //Move to the right node
    keys(current->right);
}

//Size
size_t AVLTree::size() const {
    //Return tracked size
    return num;
}

//operator[]
size_t& AVLTree::operator[](const string& key) {
    //Make a new node pointer to hold the value returned by the recursion
    AVLNode *filler = recursiveBracket(root, key);
    //Put the returned value in a size_t reference
    size_t& filler2 = filler->value;
    //Return the reference
    return filler2;
}
AVLTree::AVLNode* AVLTree::recursiveBracket(AVLNode*& current, const string& key) {
    //If nullptr is hit stop
    if (current == nullptr) {
        return nullptr;
    }
    //If the key is found return the node
    if (current->key == key) {
        return current;
    }
    //If the key is less than current key move left
    if (key < current->key) {
        return recursiveBracket(current->left, key);
    }
    //If the key is greater than current key move right
    if (key > current->key) {
        return recursiveBracket(current->right, key);
    }
    //Return
    return current;
}

//operator=
void AVLTree::operator=(const AVLTree& other) {
    //If they are already equal just stop
    if (this == &other) {
        return;
    }
    //Clear the tree being copied to
    deconstructorRecursion(this->root);
    //Set root to nullptr
    this->root = nullptr;
    //Copy over num and balance
    this->num = other.num;
    this->balance = other.balance;
    //Begin recursion
    copyEquals(this->root, other.root);
}
void AVLTree::copyEquals(AVLNode*& current, const AVLNode* other) {
    //If other is nullptr set current to nullptr and then stop
    if (other == nullptr) {
        current = nullptr;
        return;
    }
    //Make a new node that copies the key and value of other
    current = new AVLNode(other->key, other->value);
    //Copy the height of other
    current->height = other->height;
    //Move to the left node
    copyEquals(current->left, other->left);
    //Move to the right node
    copyEquals(current->right, other->right);
}

//TODO: the strange one
ostream& operator<<(ostream& os, const AVLTree & avlTree) {

}

//getHeight(tree)
size_t AVLTree::getHeight() const {
    //Return the node getHeight called with root
    return root->getHeight();
}

//AVLNode constructor
AVLTree::AVLNode::AVLNode(const string& key, size_t value) {
    //Initialize class variables
    this->key = key;
    this->value = value;
    height = 0;
    left = nullptr;
    right = nullptr;
}

//numChildren
size_t AVLTree::AVLNode::numChildren() const {
    // If the node has only one child (the left one)
    if (right != nullptr && left == nullptr) {
        return 1;
    }
    // If the node has only one child (the right one)
    if (right == nullptr && left != nullptr) {
        return 1;
    }
    // If the node is a leaf it has no children
    if (isLeaf()) {
        return 0;
    }
    // Must have both children
    return 2;
}

//isLeaf
bool AVLTree::AVLNode::isLeaf() const {
    // If the node has no children it is a leaf
    if (left == nullptr && right == nullptr) {
        return true;
    }
    // If it has a child it's not
    return false;
}

//TODO: make this actually find the height
size_t AVLTree::AVLNode::getHeight() const {
    // Returns the height
    return height;
}

//remove
bool AVLTree::remove(const string& key) {
    //begin recursion
    return remove(root, key);
}
bool AVLTree::removeNode(AVLNode*& current) {
    if (!current) {
        return false;
    }
    AVLNode* toDelete = current;
    auto nChildren = current->numChildren();
    if (current->isLeaf()) {
        // case 1 we can delete the node
        current = nullptr;
    } else if (current->numChildren() == 1) {
        // case 2 - replace current with its only child
        if (current->right) {
            current = current->right;
        } else {
            current = current->left;
        }
    } else {
        // case 3 - we have two children,
        // get the smallest key in right subtree by
        // getting right child and go left until left is null
        AVLNode* smallestInRight = current->right;
        // I could check if smallestInRight is null,
        // but it shouldn't be since the node has two children
        while (smallestInRight->left) {
            smallestInRight = smallestInRight->left;
        }
        string newKey = smallestInRight->key;
        size_t newValue = smallestInRight->value;
        remove(root, smallestInRight->key); // delete this one

        current->key = newKey;
        current->value = newValue;

        current->height = current->getHeight();
        balanceNode(current);

        return true; // we already deleted the one we needed to so return
    }
    delete toDelete;
    //Decrease size tracker by 1
    num--;
    return true;
}
bool AVLTree::remove(AVLNode *&current, const string& key) {
    //If nullptr is hit the key is not in the tree
    if (current == nullptr) {
        return false;
    }
    //If the key is found enter the actual removal process
    if (current->key == key) {
        return removeNode(current);
    }
    //If the key is less than current key move left
    if (key < current->key) {
        return remove(current->left, key);
    }
    //If the key is greater than current key more right
    if (key > current->key) {
        return remove(current->right, key);
    }
    //Return
    return true;
}

//TODO: The monster
void AVLTree::balanceNode(AVLNode *&node) {

}