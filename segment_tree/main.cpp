#include <iostream>

struct Node {
    int left;
    int right;
    int sum;
    int add;
    Node(): left(0), right(0),sum(0),add(0){}
};

const static int SIZE = 10;
Node seg_tree[4*SIZE];


void buildSegmentTree(int arr[], int left, int right, int pos);
int searchSegmentTree(int left, int right, int pos);
void updateSegmentTree();


void buildSegmentTree(int arr[], int left, int right, int pos){
    if (pos < 0 || pos >= 4*SIZE) {
        return;
    }

    seg_tree[pos].left = left;
    seg_tree[pos].right = right;

    if (left == right) {
        seg_tree[pos].sum = arr[left];
        return;
    }

    int lson = 2*pos + 1;
    int rson = 2*pos + 2;

    int mid = (left + right) >> 1;

    buildSegmentTree(arr, left, mid, lson);
    buildSegmentTree(arr, mid+1, right, rson);

    seg_tree[pos].sum = seg_tree[lson].sum + seg_tree[rson].sum;
    
}

//4,6  0,9
int searchSegmentTree(int left, int right, int pos) {
    if (left <= seg_tree[pos].left && right >= seg_tree[pos].right) {
        return seg_tree[pos].sum;
    }

    int lson = pos * 2 + 1;
    int rson = pos * 2 + 2;
    int ret = 0;
    if (seg_tree[lson].right >= left) {
        ret += searchSegmentTree(left, right, lson);
    }
    if (seg_tree[rson].left <= right) {
        ret += searchSegmentTree(left, right, rson);
    }
    return ret;
}

void updateSegmentTree(){}

void test_build_tree(int arr[]) {
    int index = 0;
    while(seg_tree[index].sum!=0) {
        int sum = 0;
        for (int i = seg_tree[index].left; i <= seg_tree[index].right; i++) {
            sum += arr[i];
        }
        if (seg_tree[index].sum == sum) {
            printf("[%d, %d] = %d\n", seg_tree[index].left, seg_tree[index].right, sum);
        } else {
            printf("error \n");
            while(1);
        }
        index++;
    }
}


int main() {

    int arr[SIZE] = {9, 4, 12, 99, 2, 3, 50, 30, 5, 10};

    buildSegmentTree(arr, 0, SIZE - 1, 0);
    test_build_tree(arr);
    
    int ret = searchSegmentTree(0, 8, 0);
    printf("ret = %d", ret);

    updateSegmentTree();

    return 0;
}