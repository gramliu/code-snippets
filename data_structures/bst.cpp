#ifndef BST_H
#define BST_H

/*
Binary Search Tree
*/

#include "../util/util.h";
#include <stdlib.h>

// Comparison function to compare two elements
typedef int compare_fn(entry x, entry y);

struct bst {
    entry data;
    bst* left;
    bst* right;
};

bool is_tree(bst* B) {
    if (B == NULL) return true;
    return B->data != NULL && is_tree(B->left) && is_tree(B->right);
}

bool is_ordered(bst* B, entry lo, entry hi, compare_fn* cmp) {
    if (B == NULL) return true;
    if (lo != NULL && (*cmp)(lo, B->data) != -1) return false;
    if (hi != NULL && (*cmp)(B->data, hi) != 1) return false;
    return is_ordered(B->left, lo, B->data) && is_ordered(B->right, B->data, hi);
}

bool is_bst(bst* B, compare_fn* cmp) {
    return is_tree(B) && is_ordered(B, NULL, NULL, cmp);
}

bst* bst_leaf(entry val) {
    bst* B = (bst*) calloc(1, sizeof(bst));
    B->data = val;
    return B;
}

bst* bst_insert(bst* B, entry data, compare_fn* cmp) {
    REQUIRES(is_bst(B, cmp));
    if (B == NULL) {
        B = bst_leaf(B);
    }
    int result = (*cmp) (B->data, data);
    if (cmp < 0) {
        B->left = bst_insert(B->left, data, cmp);
    } else if (cmp > 0) {
        B->right = bst_insert(B->right, data, cmp);
    }
    ENSURES(is_bst(B));
    return B;
}

entry bst_lookup(bst* B, entry data, compare_fn* cmp) {
    REQUIRES(is_bst(B));
    if (B == NULL) return NULL;
    int result = (*cmp)(data, B->data);
    entry ans = NULL;
    if (result == 0) {
        ans = B->data;
    } else if (result < 0) {
        ans = bst_lookup(B->left, data, cmp);
    } else {
        ans = bst_lookup(B->right, data, cmp);
    }
    ENSURES(ans == NULL || is_bst(ans));
    return ans;
}

#endif