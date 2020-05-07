#ifndef AVL_H
#define AVL_H

/*
AVL Tree Data Structure
Self-balancing binary tree with contracts
*/

#include <cstdlib>

#include "../util/util.h";

struct avl {
    int height;
    int val;
    avl* left;
    avl* right;
};

bool is_avl(avl* T) {}

avl* leaf(int val) {
    avl* leaf = (avl*)calloc(1, sizeof(avl));
    leaf->val = val;
    ENSURES(is_avl(leaf));
    return leaf;
}

int height(avl* T) {
    if (T == NULL) return -1;
    return T->height;
}

void fix_height(avl* T) {
    int hl = height(T->left);
    int hr = height(T->right);
    T->height = (hl > hr ? hl + 1 : hr + 1);
}

avl* rotate_left(avl* T) {
    avl* right = T->right;
    T->right = right->left;
    right->left = T;
    fix_height(T);
    fix_height(right);
    return right;
}

avl* rotate_right(avl* T) {
    avl* left = T->left;
    T->left = left->right;
    left->right = T;
    fix_height(T);
    fix_height(left);
    return left;
}

avl* rebalance_left(avl* T) {
    if (height(T->left) - height(T->right) == 2) {
        if (height(T->left->left) > height(T->left->right)) {
            T = rotate_right(T);
        } else {
            T->left = rotate_left(T->left);
            T = rotate_right(T);
        }
    } else {
        fix_height(T);
    }
    return T;
}

avl* rebalance_right(avl* T) {
    if (height(T->right) - height(T->left) == 2) {
        if (height(T->right->right) > height(T->right->left)) {
            T = rotate_left(T);
        } else {
            T->right = rotate_right(T->right);
            T = rotate_left(T);
        }
    } else {
        fix_height(T);
    }
    return T;
}

avl* insert(avl* T, int val) {
    if (T == NULL) return leaf(val);
    if (val < T->val) {
        T->left = insert(T->left, val);
        T = rebalance_left(T);
    } else if (val > T->val) {
        T->right = insert(T->right, val);
        T = rebalance_right(T);
    }
    return T;
}

#endif