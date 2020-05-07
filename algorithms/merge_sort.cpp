#ifndef MERGE_SORT_H
#define MERGE_SORT_H

#include <stdlib.h>

void merge(int* arr, int lo1, int lo2, int hi) {
    int* tmp = (int*) malloc((hi - lo1) * sizeof(int));
    int i = lo1;
    int j = lo2;
    int idx = 0;
    while (i < lo2 && j < hi) {
        if (arr[i] < arr[j]) {
            tmp[idx++] = arr[i++];
        } else {
            tmp[idx++] = arr[j++];
        }
    }
    while (i < lo2) tmp[idx++] = arr[i++];
    while (j < hi) tmp[idx++] = arr[j++];
    for (idx = 0; idx < hi - lo1; idx++) {
        arr[lo1 + idx] = tmp[idx];
    }
}

void merge_sort_util(int* arr, int lo, int hi) {
    if (hi - lo > 1) {
        int mid = lo + (hi - lo) / 2;
        merge_sort_util(arr, lo, mid);
        merge_sort_util(arr, mid, hi);
        merge(arr, lo, mid, hi);
    }
}

void merge_sort(int* arr, int n) {
    merge_sort_util(arr, 0, n);
}

#endif