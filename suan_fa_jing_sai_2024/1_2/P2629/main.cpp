/*
用前缀和也可以
https://blog.csdn.net/wkyhnyq/article/details/130875484
*/

#include <iostream>
#include <stdio.h>

using namespace std;

#define MAX_SZ 1000005

struct NODE{
    int val;
    int ind;
    NODE():val(0), ind(0){}
};

struct QUEUE{
    QUEUE():f(0),t(0){}
    void push(int v, int i) {
        NODE* n = &q[t++];
        n->val = v;
        n->ind = i;
    }
    void popFront() {f++;}
    void popTail() {t--;}
    NODE* front() {return &q[f];}
    NODE* tail() {return &q[t-1];}
    bool isEmpty() {return f == t;}
    int size() {return t - f;}
    int f;
    int t;
    NODE q[MAX_SZ];
};

int a[MAX_SZ * 2];

int main() {
    freopen("input.txt", "r", stdin);
    setbuf(stdout, NULL);
    int n,k;
    cin >> n;
    QUEUE Q;

    int index = -1;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        Q.push(a[i], i);
    }

    NODE* node;
    NODE* node_t;
    while(n--) {
        node = Q.front();
        Q.popFront();
        if (node->val >= 0) {
            Q.push(node->val, node->ind);
        } else {
            node_t = Q.tail();
            while(node_t->val + node->val < 0) {
                node->val += node_t->val;
                Q.popTail();
                node_t = Q.tail();
            }
            node_t->val += node->val;
        }
    }

    cout << Q.size() << endl;

    return 0;
}