#include "main.h"
//#include "heap.cpp"

void swap(int& x, int& y);
void heapup_sort(int arr[], int n);


int main() {
    int size = 10;
    int arr[10] = {9, 4, 12, 99, 2, 3, 50, 30,0, 10};

    heapup_sort(arr, size);

    for (int i = 0; i < 10; i++) {
        printf("%d ", arr[i]);
    }

    return 0;
}