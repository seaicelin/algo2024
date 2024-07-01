#include <stdio.h>

#define MAX_SZ 2000005

struct NODE {
    int val;
    int ind;
    NODE():val(0),ind(0){}
};

struct QUEUE{
    QUEUE():f(0),t(0){}
    void push(int v, int i){
        q[t].val = v;
        q[t].ind = i;
        t++;
    }
    void popFront() {f++;}
    void popTail() {t--;}
    bool isEmpty() {return f == t;}
    NODE* front() {return &q[f];}
    NODE* tail() {return &q[t-1];}
    void reset() {f = t = 0;}
    int f;
    int t;
    NODE q[MAX_SZ];
};

int a[MAX_SZ];

int main() {
    freopen("input.txt", "r", stdin);
    setbuf(stdout, NULL);
    int n,m;
    scanf("%d %d", &n, &m);
    QUEUE Q;
    NODE* node;
    for (int i = 1; i <= n; i++) {
        scanf("%d", &a[i]);
        node = Q.front();
        while(!Q.isEmpty() && node->ind < i - m) {
            Q.popFront();
            node = Q.front();
        }
        printf("%d\n", node->val);
        node = Q.tail();
        while(!Q.isEmpty() && node->val >= a[i]) {
            Q.popTail();
            node = Q.tail();
        }
        Q.push(a[i], i);
    }
    return 0;
}