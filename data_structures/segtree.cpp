#ifndef SEGTREE_LAZY_H
#define SEGTREE_LAZY_H

/*
Segment tree
Point updates with range query
*/

#include <stdlib.h>

struct segtree {
    int start;
    int end;

    int val;

    segtree* left;
    segtree* right;
};

segtree* make_segtree(int start, int end, int* A) {
    segtree* tree = (segtree*) calloc(1, sizeof(segtree));
    tree->start = start;
    tree->end = end;
    if (start != end) {
        int mid = start + (end - start) / 2;
        tree->left = make_segtree(start, mid, A);
        tree->right = make_segtree(mid+1, end, A);
        tree->val = tree->left->val + tree->right->val;
    } else {
        tree->val = A[start];
    }
    return tree;
}

void update(segtree* tree, int idx, int diff) {
    if (tree->start > idx || tree->end < idx) return;
    tree->val += diff;
    if (tree->start != tree->end) {
        update(tree->left, idx, diff);
        update(tree->right, idx, diff);
    }
}

int query(segtree* tree, int start, int end) {
    if (start > tree->end || end < tree->start) return 0;
    if (start <= tree->start && tree->end <= end) {
        return tree->val;
    }
    return query(tree->left, start, end) + query(tree->right, start, end);
}

#endif