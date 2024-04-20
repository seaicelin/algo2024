#include "main.h"
#if v40

#include <stdio.h>

struct Node{
    char v;
    char n;
    Node& operator=(Node& c){
        v = c.v;
        n = c.n;
        return *this;
    }
}node_list[101];

int main() {

    freopen("input.txt", "r", stdin);

    int n,m;
    scanf("%d %d",&n, &m);

    for (int k = 1; k <= n; k++) {
        node_list[k].v = k;
        node_list[k].n = k+1;
    }
    node_list[n].n = 1;

    char mod = m;
    char cur = 1, prev;
    while(n) {
        prev = cur;
        cur = node_list[cur].n;
        mod--;
        if (mod == 0) {
            mod =m;
            n--;
            printf("%d ", node_list[prev].v);
            node_list[prev] = node_list[cur];
        }
    }

    return 0;
}

#endif