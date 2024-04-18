#include "main.h"



int parent(int pos) {
    return (pos - 1) / 2;
}

void swap(int& a, int& b) {
    int c = a;
    a = b;
    b = c;
}

void shipdown(int arr[], int pos, int size) {
    int l, r, max;
    while(true) {
        max = pos;
        l = 2 * pos + 1;
        r = 2 * pos + 2;
        if (l < size && arr[max] < arr[l]) {
            max = l;
        }
        if (r < size && arr[max] < arr[r]) {
            max = r;
        }
        if (pos == max) break;

        swap(arr[pos], arr[max]);
        pos = max;
    }
}

void heap_sort(int arr[], int size) {
    for (int i = parent(size-1); i >= 0; i--) {
        shipdown(arr, i, size);
    }

    for (int i = size - 1; i > 0; i--) {
        swap(arr[i], arr[0]);
        shipdown(arr, 0, i-1);
    }
}