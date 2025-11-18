#include "AVLTree.h"
#include <string>
#include <optional>
#include <vector>

using namespace std;

AVLTree::AVLTree() {
    balance = 0;
    num = 0;
    root = nullptr;
}

AVLTree::AVLTree(const AVLTree& other) {
    this->balance = other.balance;
    this->num = other.num;
    this->root = nullptr;
    copyConstructorRecursion(this->root, other.root);
}
void AVLTree::copyConstructorRecursion(AVLNode*& current, const AVLNode* other) {
    if (other == nullptr) {
        current = nullptr;
        return;
    }
    current = new AVLNode(other->key, other->value);
    current->height = other->height;
    copyConstructorRecursion(current->left, other->left);
    copyConstructorRecursion(current->right, other->right);
}

AVLTree::~AVLTree() {
    deconstructorRecursion(root);
    root = nullptr;
    num = 0;
    balance = 0;
}
void AVLTree::deconstructorRecursion(AVLNode*& current) {
    if (current == nullptr) {
        return;
    }
    deconstructorRecursion(current->left);
    deconstructorRecursion(current->right);
    delete current;
    current = nullptr;
}

bool AVLTree::insert(const string& key, const size_t value) {
    return insert(root, key, value);
}
bool AVLTree::insert(AVLNode*& current, const string& key, const size_t& value) {
    if (current == nullptr) {
        current = new AVLNode (key, value);
        num++;
        return true;
    }
    if (contains(current, key)) {
        return false;
    }
    bool inserted = false;
    if (key < current->key) {
        inserted = insert(current->left, key, value);
    }
    else if (key > current->key) {
        inserted = insert(current->right, key, value);
    }
    return inserted;
}

bool AVLTree::contains(const string& key) {
    return contains(root, key);
}
bool AVLTree::contains(AVLNode*& current, const string& key) const {
    if (current == nullptr) {
        return false;
    }
    if (current->key == key) {
        return true;
    }
    bool contained = false;
    if (key < current->key) {
        contained = contains(current->left, key);
    }
    else if (key > current->key) {
        contained = contains(current->right, key);
    }
    return contained;
}

optional<size_t> AVLTree::get(const string& key) {
    return get(root, key);
}
optional<size_t> AVLTree::get(AVLNode*& current, const string& key) const {
    optional<size_t> gotten{};
    if (!contains(current, key)) {
        return nullopt;
    }
    if (current->key == key) {
        gotten = current->value;
        return gotten;
    }
    if (key < current->key) {
        gotten = get(current->left, key);
    }
    else if (key > current->key) {
        gotten = get(current->right, key);
    }
    return gotten;
}

vector<string> AVLTree::findRange(const string& lowKey, const string& highKey) {
    range.clear();
    findRange(root, lowKey, highKey);
    return range;
}
void AVLTree::findRange(AVLNode*& current, const string& lowKey, const string& highKey) {
    if (current == nullptr) {
        return;
    }
    if (current->key <= lowKey && current->key >= highKey) {
        range.push_back(current->key);
    }
    findRange(current->left, lowKey, highKey);
    findRange(current->right, lowKey, highKey);
}

vector<string> AVLTree::keys() {
    range.clear();
    keys(root);
    return range;
}
void AVLTree::keys(AVLNode*& current) {
    if (current == nullptr) {
        return;
    }
    range.push_back(current->key);
    keys(current->left);
    keys(current->right);
}

size_t AVLTree::size() const {
    return num;
}

size_t& AVLTree::operator[](const string& key) {
    AVLNode *filler = recursiveBracket(root, key);
    size_t& filler2 = filler->value;
    return filler2;
}
AVLTree::AVLNode* AVLTree::recursiveBracket(AVLNode*& current, const string& key) {
    if (current == nullptr) {
        return nullptr;
    }
    if (current->key == key) {
        return current;
    }
    if (key < current->key) {
        return recursiveBracket(current->left, key);
    }
    if (key > current->key) {
        return recursiveBracket(current->right, key);
    }
    return current;
}

size_t AVLTree::getHeight() const {
    return root->height;
}

AVLTree::AVLNode::AVLNode(const string& key, size_t value) {
    this->key = key;
    this->value = value;
    height = 0;
    left = nullptr;
    right = nullptr;
}

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

bool AVLTree::AVLNode::isLeaf() const {
    // If the node has no children it is a leaf
    if (left == nullptr && right == nullptr) {
        return true;
    }
    // If it has a child it's not
    return false;
}

size_t AVLTree::AVLNode::getHeight() const {
    // Returns the height
    return height;
}

bool AVLTree::remove(const string& key) {
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
    num--;
    return true;
}
bool AVLTree::remove(AVLNode *&current, const string& key) {
    if (current == nullptr) {
        return false;
    }
    if (current->key == key) {
        return removeNode(current);
    }
    if (key < current->key) {
        return remove(current->left, key);
    }
    if (key > current->key) {
        return remove(current->right, key);
    }
    return true;
}

void AVLTree::balanceNode(AVLNode *&node) {

}