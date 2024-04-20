#include "main.h"
#if v50

#include <stdio.h>

char q[10005];
struct queue{
    queue(char* q):f(0),t(0),mQ(q) {}
    void pop() {f++;}
    void push(char e) {mQ[t++] = e;}
    int front() {return mQ[f];}
    bool isEmpty() {return t - f == 0;}
    char* mQ;
    int f;
    int t;  
};

int main() {

    freopen("input.txt", "r", stdin);

    int n,m;
    scanf("%d %d",&n, &m);

    queue Q(q);

    for (int k = 1; k <= n; k++) {
        Q.push(k);
    }

    char mod = m;
    while(!Q.isEmpty()) {
        char v = Q.front();
        Q.pop();
        mod--;
        if (mod == 0) {
            mod =m;
            printf("%d ", v);
            continue;
        }
        Q.push(v);
    }

    return 0;
}

#endif