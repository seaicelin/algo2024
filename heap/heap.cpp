
void swap(int& x, int& y) {
    int temp = x;
    x = y;
    y = temp;
}

void heapAdd(int arr[],int n, int val) {
    

}

 /*
* 维护堆的性质
* @param arr 存储堆的数组
* @param n 数组的长度
* @param i 待维护节点的下标
*/
void heapfy(int arr[], int n, int i) {
    int largest = i;
    int lson = i * 2 + 1;
    int rson = i * 2 + 2;
    if (lson < n && arr[largest] < arr[lson]) {
        largest = lson;
    }
    if (rson < n && arr[largest] < arr[rson]) {
        largest = rson;
    }

    if (largest != i) {
        swap(arr[largest], arr[i]);
        heapfy(arr, n, largest);
    }

}

void heapup(int arr[], int n, int i) {
    if (i >= n) {
        return;
    }
    int largest = i;
    int lson = 2*i + 1;
    int rson = 2*i + 2;
    if (lson < n && arr[largest] < arr[lson]) {
        largest = lson;
    }
    if (rson < n && arr[largest] < arr[rson]) {
        largest = rson;
    }
    if (largest != i) {
        swap(arr[largest], arr[i]);
        heapup(arr, n, largest);
    }
}

void build_heap(int arr[], int n) {
    for (int i = n/2 -1; i >= 0; i--) {
        heapup(arr, n, i);
    }
}

void heapup_sort(int arr[], int n) {

    build_heap(arr, n);

    for (int i = n-1; i >=0; i--) {
        swap(arr[i], arr[0]);
        heapup(arr, i, 0);
    }
}


void heap_sort(int arr[], int n) {

    //建堆过程，注意这里i的起始取值，n/2 - 1, 比这个大都是叶子节点了，没有子节点。逐个往上建堆
    for(int i = n/2 - 1; i >= 0; i--) {
        heapfy(arr, n, i);
    }

    for (int i = n - 1; i >= 0; i--) {
        swap(arr[i], arr[0]);
        heapfy(arr, n, 0);
    }

}