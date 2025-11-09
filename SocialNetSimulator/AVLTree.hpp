#ifndef AVLTREE_HPP
#define AVLTREE_HPP

#include "Post.hpp"
#include <iostream>
#include <algorithm>

/**
 * @class AVLNode
 * @brief Represents a node in the AVL Tree.
 * Each node holds a Post and pointers to its children, plus its height.
 */
class AVLNode {
public:
    Post post;
    AVLNode *left;
    AVLNode *right;
    int height;

    AVLNode(Post p) : post(p), left(nullptr), right(nullptr), height(1) {}
};

/**
 * @class AVLTree
 * @brief An implementation of a self-balancing AVL Tree.
 * This tree stores a user's posts, sorted by postID.
 */
class AVLTree {
private:
    AVLNode* root;
    int getHeight(AVLNode* node);
    int getBalance(AVLNode* node);
    AVLNode* rightRotate(AVLNode* y);
    AVLNode* leftRotate(AVLNode* x);
    AVLNode* insert(AVLNode* node, Post post);
    void reverseInOrder(AVLNode* node, int& count, int N);
    void deleteTree(AVLNode* node);

public:
    AVLTree();
    ~AVLTree();
    void insert(Post post);
    void outputPosts(int N);
};

#endif 