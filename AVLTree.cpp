#include "AVLTree.h"
#include <string>

size_t AVLTree::AVLNode::numChildren() const {
    // If the node has only one child (the left one)
    if (this->right != nullptr && this->left == nullptr) {
        return 1;
    }
    // If the node has only one child (the right one)
    if (this->right == nullptr && this->left != nullptr) {
        return 1;
    }
    // If the node is a leaf it has no children
    if (isLeaf()) {
        return 0;
    }
    // Must have both children
    return 2;
}

bool AVLTree::AVLNode::isLeaf() const {
    // If the node has no children it is a leaf
    if (this->left == nullptr && this->right == nullptr) {
        return true;
    }
    // If it has a child it's not
    return false;
}

size_t AVLTree::AVLNode::getHeight() const {
    return 0;
}

bool AVLTree::removeNode(AVLNode*& current){
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
        std::string newKey = smallestInRight->key;
        int newValue = smallestInRight->value;
        remove(root, smallestInRight->key); // delete this one

        current->key = newKey;
        current->value = newValue;

        current->height = current->getHeight();
        balanceNode(current);

        return true; // we already deleted the one we needed to so return
    }
    delete toDelete;

    return true;
}

bool AVLTree::remove(AVLNode *&current, KeyType key) {
    return false;
}

void AVLTree::balanceNode(AVLNode *&node) {

}