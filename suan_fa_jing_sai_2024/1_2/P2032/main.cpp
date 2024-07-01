#include <iostream>
#include <stdio.h>

using namespace std;

#define MAX_SZ 2000005

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
    int f;
    int t;
    NODE q[MAX_SZ];
};

int main() {
    freopen("input.txt", "r", stdin);
    setbuf(stdout, NULL);
    int n,k;
    cin >> n >> k;
    int a;
    QUEUE Q;
    NODE* node;
    for (int i = 1; i <= n; i++) {
        cin >> a;
        node = Q.front();
        while(!Q.isEmpty() && node->ind < i - k + 1) {
            Q.popFront();
            node = Q.front();
        }
        node = Q.tail();
        while(!Q.isEmpty() && node->val <= a) {
            Q.popTail();
            node = Q.tail();
        }
        Q.push(a, i);
        if (i >= k) {
            cout << Q.front()->val << endl;
        }
    }
    return 0;
}