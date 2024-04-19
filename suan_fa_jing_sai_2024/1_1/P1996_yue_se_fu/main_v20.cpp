#include "main.h"
#if v20

#include <iostream>

using namespace std;

struct Node{
    int v;
    Node* next;
};

Node node_list[1001];

int main() {

    freopen("input.txt", "r", stdin);

    int n,m;
    cin >> n >> m;

    Node* cur;
    for (int i = 1; i <= n; i++) {
        cur = &node_list[i];
        cur->v = i;
        if (i < n)
            cur->next = &node_list[i+1];
        else 
            cur->next = &node_list[1];
    }
    int mod = m;
    cur = &node_list[1];
    Node* prev;
    while(n) {
        prev = cur;
        cur = cur->next;
        mod--;
        if (mod == 0) {
            mod =m;
            n--;
            cout << prev->v << " ";
            prev->v = cur->v;
            prev->next = cur->next;
        }
    }


    return 0;
}

#endif