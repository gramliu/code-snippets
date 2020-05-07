#ifndef UFDS_H
#define UFDS_H

/*
Union-Find Disjoint Sets
Disjoint Set data structure for handling union find
with path compression and height tracking
*/

#include <stdlib.h>

struct ufds {
    int height;
    int parent;
};

ufds* make_ufds(int n) {
    ufds* ds = (ufds*) calloc(n, sizeof(ufds));
    for (int i = 0; i < n; i++) {
        ds[i].parent = i;
    }
    return ds;
}

int findParent(ufds* ds, int n) {
    if (ds[n].parent != n) {
        ds[n].parent = findParent(ds, ds[n].parent);
    }
    return ds[n].parent;
}

void doUnion(ufds* ds, int a, int b) {
    int pa = findParent(ds, a);
    int pb = findParent(ds, b);
    if (ds[pa].height > ds[pb].height) {
        ds[pb].parent = pa;
        ds[pb].height = 0;
    } else if (ds[pa].height < ds[pb].height) {
        ds[pa].parent = pb;
        ds[pa].height = 0;
    } else {
        ds[pb].parent = pa;
        ds[pa].height++;
        ds[pb].height = 0;
    }
}

#endif