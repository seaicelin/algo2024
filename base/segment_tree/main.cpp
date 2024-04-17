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
void updateSegmentTree(int left, int right, int add, int pos);
void update(int pos, int x, int k);
int query(int pos, int x, int y);
void update(int pos, int x, int y, int k);

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

int query(int pos, int x, int y) {
    if (seg_tree[pos].left >= x && seg_tree[pos].right <= y) {
        return seg_tree[pos].sum;
    }

    int lson = pos * 2 + 1;
    int rson = pos * 2 + 2;
    int mid = (seg_tree[pos].left + seg_tree[pos].right) / 2;

    int sum = 0;
    if (x <= mid) {
        sum += query(lson, x, y);
    }
    if (y > mid) {
        sum += query(rson, x, y);
    }

    return sum;
}

void test_query(int arr[]) {
    for (int i = 0; i < SIZE; i++) {
        int sum = arr[i];
        for (int j = i + 1; j < SIZE; j++) {
            sum += arr[j];
            if (sum != query(0, i, j)) {
                printf("test_query error \n");
                return;
            }
        }
    }
    printf("test_query success!\n");
}

void updateSegmentTree(int left, int right, int add, int pos) {
    if (left <= seg_tree[pos].left && right >= seg_tree[pos].right) {
        seg_tree[pos].add = add;
        return;
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
}

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
            printf("test_build_tree error \n");
            return;
            //while(1);
        }
        index++;
    }
}



void test_search_seg_tree(int arr[]) {
    for (int i = 0; i < SIZE; i++) {
        int sum = arr[i];
        for (int j = i; j < SIZE; j++) {
            if (i != j) {
                sum += arr[j];
            }
            if (sum != searchSegmentTree(i, j, 0)) {
                printf("test_search_seg_tree i=%d, j = %d sum = %d error \n",i,j,sum);
                return;
            }
        }
    }
    printf("test_search_seg_tree success!\n");
}

void update(int pos, int x, int k) {
    if (seg_tree[pos].left == x && seg_tree[pos].right == x) {
        seg_tree[pos].sum += k;
        return;
    }
    int lson = pos * 2 + 1;
    int rson = pos * 2 + 2;
    int mid = (seg_tree[pos].left + seg_tree[pos].right) / 2;
    if (x <= mid) {
        update(lson, x, k);
    }
    if (x > mid) {
        update(rson, x, k);
    }
    seg_tree[pos].sum = seg_tree[lson].sum + seg_tree[rson].sum;
}

void test_update(int arr[]) {
    for (int i = 0; i < SIZE; i++) {
        int sum = arr[i] += 5;
        update(0, i, 5);
        for (int j = i + 1; j < SIZE; j++) {
            sum += arr[j];
            if (sum != query(0, i, j)) {
                printf("test_udpate error \n");
                return;
            }
        }
    }
    printf("test_udpate success!\n");
}

void pushdown(int pos) {
    if (seg_tree[pos].add) {
        int lson = pos*2 + 1;
        int rson = pos*2 + 2;
        seg_tree[lson].sum += seg_tree[pos].add * (seg_tree[lson].right - seg_tree[lson].left + 1);
        seg_tree[rson].sum += seg_tree[pos].add * (seg_tree[rson].right - seg_tree[lson].left + 1);
        seg_tree[lson].add += seg_tree[pos].add;
        seg_tree[rson].add += seg_tree[pos].add;
        seg_tree[pos].add = 0;
    }
}

void pushup(int pos) {
    seg_tree[pos].sum = seg_tree[2*pos+1].sum + seg_tree[2*pos+2].sum;
}

void update(int pos, int x, int y, int k) {
    if(seg_tree[pos].left >= x && seg_tree[pos].right <= y) {
        seg_tree[pos].sum += (seg_tree[pos].right - seg_tree[pos].left + 1) * k;
        seg_tree[pos].add += k;
        return;
    }
    int lson = pos*2 + 1;
    int rson = pos*2 + 1;
    int mid = seg_tree[pos].left + seg_tree[pos].right >> 1;
    pushdown(pos);
    if (x <= mid) {
        update(lson, x, y, k);
    }
    if (y > mid) {
        update(rson, x, y, k);
    }
    pushup(pos);
}

int main() {

    int arr[SIZE] = {9, 4, 12, 99, 2, 3, 50, 30, 5, 10};

    buildSegmentTree(arr, 0, SIZE - 1, 0);
    test_build_tree(arr);
    
    //int ret = searchSegmentTree(0, 8, 0);
    //printf("ret = %d\n", ret);
    test_search_seg_tree(arr);
    test_query(arr);
    test_update(arr);

    //updateSegmentTree(0, 5, 5);

    return 0;
}