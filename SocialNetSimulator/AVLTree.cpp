#include "AVLTree.hpp"
#include <algorithm>
#include <cstdint>
using namespace std;

// Public Interface 

AVLTree::AVLTree() : root(nullptr) {}

AVLTree::~AVLTree() {
    deleteTree(root);
}

void AVLTree::insert(Post post) {
    root = insert(root, post);
}

void AVLTree::outputPosts(int N) {
    if (N == -1) {
        N = INT32_MAX; 
    }
    int count = 0;
    reverseInOrder(root, count, N);
}

// Private Helper Functions 

int AVLTree::getHeight(AVLNode* node) {
    if (node == nullptr)
        return -1;
    return node->height;
}

int AVLTree::getBalance(AVLNode* node) {
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

AVLNode* AVLTree::rightRotate(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    return x;
}

AVLNode* AVLTree::leftRotate(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
    y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
    return y;
}

AVLNode* AVLTree::insert(AVLNode* node, Post post) {
    if (node == nullptr) {
        return(new AVLNode(post));
    }
    if (post < node->post) {
        node->left = insert(node->left, post);
    } else if (post > node->post) {
        node->right = insert(node->right, post);
    } else {
        return node;
    }
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && post < node->left->post)
            return rightRotate(node);

    // Right Right Case
    if (balance < -1 && post > node->right->post)
        return leftRotate(node);
    
    // Left Right Case
    if (balance > 1 && post > node->left->post) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && post < node->right->post) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }    
    return node;
}

void AVLTree::reverseInOrder(AVLNode* node, int& count, int N) {
    if (node == nullptr || count >= N)
        return;
    reverseInOrder(node->right, count, N);
    if (count < N) {
        cout << "Content: " << node->post.content << endl;
        count++;
    }
    reverseInOrder(node->left, count, N);
}

void AVLTree::deleteTree(AVLNode* node) {
    if (node != nullptr) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}