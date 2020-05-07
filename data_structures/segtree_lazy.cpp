#ifndef SEGTREE_LAZY_H
#define SEGTREE_LAZY_H

/*
Segment tree with lazy propagation
Range updates with range query
*/

#include <stdlib.h>

struct segtree {
    int start;
    int end;

    int val;
    int prop;

    segtree* left;
    segtree* right;
};

segtree* make_segtree(int start, int end) {
    segtree* tree = (segtree*) calloc(1, sizeof(segtree));
    tree->start = start;
    tree->end = end;
    if (start != end) {
        int mid = start + (end - start) / 2;
        tree->left = make_segtree(start, mid);
        tree->right = make_segtree(mid+1, end);
    }
    return tree;
}

void propagate(segtree* tree) {
    int start = tree->start;
    int end = tree->end;
    tree->val += tree->prop;
    if (end != start) {
        tree->left->prop += tree->prop;
        tree->right->prop += tree->prop;
    }
    tree->prop = 0;
}

void updateRange(segtree* tree, int start, int end, int diff) {
    if (tree->prop != 0) {
        propagate(tree);
    }
    if (start > tree->end || end < tree->start) return;
    if (start <= tree->start && tree->end <= end) {
        tree->val += (tree->end - tree->start + 1) * diff;
        if (tree->end != tree->start) {
            tree->left->prop += diff;
            tree->right->prop += diff;
        }
        return;
    }
    updateRange(tree->left, start, end, diff);
    updateRange(tree->right, start, end, diff);
    tree->val = tree->left->val + tree->right->val;
}

int query(segtree* tree, int start, int end) {
    if (tree->prop != 0) {
        propagate(tree);
    }
    if (start > tree->end || end < tree->start) return 0;
    if (start <= tree->start && tree->end <= end) {
        return tree->val;
    }
    return query(tree->left, start, end) + query(tree->right, start, end);
}

#endif