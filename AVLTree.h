/**
 * AVLTree.h
 */

#ifndef AVLTREE_H
#define AVLTREE_H
#include <optional>
#include <string>
#include <vector>

using namespace std;

class AVLTree {
public:

    size_t balance;
    size_t num;

    AVLTree();

    bool insert(const string& key, size_t value);
    bool remove(const string& key);
    bool contains(const string& key);
    optional<size_t> get(const string& key);
    size_t& operator[](const string& key);
    vector<string> findRange(const string& lowKey, const string& highKey) const;
    vector<string> keys() const;
    size_t size() const;
    size_t getHeight() const;
    AVLTree(const AVLTree& other);
    void operator=(const AVLTree& other);
    ~AVLTree();
    friend ostream& operator<<(ostream& os, const AVLTree & avlTree);

protected:
    class AVLNode {
    public:

        string key;
        size_t value;
        size_t height;

        AVLNode* left;
        AVLNode* right;

        AVLNode(const string& key, size_t value);

        // 0, 1 or 2
        size_t numChildren() const;
        // true or false
        bool isLeaf() const;
        // number of hops to deepest leaf node
        size_t getHeight() const;

    };

    public:
        AVLNode recursiveBracket(AVLNode*& current);
        AVLNode deconstructor(AVLNode*& current);

    private:
        AVLNode* root;

        static bool insert(AVLNode*& current, const string& key, const size_t& value);
        static bool contains(AVLNode*& current, const string &key);
        static optional<size_t> get(AVLNode*& current, const string& key);
        vector<string> findRange(AVLNode*& current, const string& lowKey, const string& highKey) const;
        vector<string> keys(AVLNode*& current) const;
        AVLTree(AVLNode*& current, AVLTree& other);
        void copyEquals(AVLNode& current, AVLNode& other);


        /* Helper methods for remove */
        // this overloaded remove will do the recursion to remove the node
        bool remove(AVLNode*& current, string key);
        // removeNode contains the logic for actually removing a node based on the number of children
        bool removeNode(AVLNode*& current);
        // You will implement this, but it is needed for removeNode()
        void balanceNode(AVLNode*& node);
};

#endif //AVLTREE_H
