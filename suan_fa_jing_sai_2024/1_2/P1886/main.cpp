#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

#define MAX_SZ 1000005

struct NODE {
    int val;
    int cnt;
};

int front, tail;

struct Queue {
    Queue():f(0), t(0) {}
    void push(int val, int cnt) {
        q[t].val = val;
        q[t].cnt = cnt;
        t++;
    }
    void popTail() {t--;}
    void popFront() {f++;}
    NODE* front() {return &q[f];}
    NODE* tail() {return &q[t-1];}
    bool isEmpty() {return f == t;}
    void reset() {f = t = 0;}
    int f;
    int t;
    NODE q[MAX_SZ];
};

int a[MAX_SZ];

int main() {
    freopen("input.txt", "r", stdin);
    setbuf(stdout, NULL);

    int n, k;
    scanf("%d %d", &n, &k);

    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
    }

    Queue Q;
    NODE* node;
    for (int i = 1; i <= n; i++) {
        while (!Q.isEmpty()) {
            node = Q.tail();
            if(a[i] <= node->val) {
                Q.popTail();
            } else {
                break;
            }
        }
        Q.push(a[i], i);
        if (i >= k) {
            node = Q.front();
            while (node->cnt < i - k + 1) {
                Q.popFront();
                node = Q.front();
            }
            printf("%d ", node->val);
        }
    }
    printf("\n");

    Q.reset();
    for (int i = 1; i <= n; i++) {
        while (!Q.isEmpty()) {
            node = Q.tail();
            if(a[i] >= node->val) {
                Q.popTail();
            } else {
                break;
            }
        }
        Q.push(a[i], i);
        if (i >= k) {
            node = Q.front();
            while (node->cnt < i - k + 1) {
                Q.popFront();
                node = Q.front();
            }
            printf("%d ", node->val);
        }
    }

    return 0;
}