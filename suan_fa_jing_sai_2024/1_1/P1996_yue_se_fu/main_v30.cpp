#include "main.h"
#if v30

#include <iostream>

using namespace std;

struct Node{
    int v;
    Node* next;
    Node* prev;
};

Node node_list[1001];

int main() {

    freopen("input.txt", "r", stdin);

    int n,m;
    cin >> n >> m;

    int i = 1;
    Node *cur;
    Node *ns = &node_list[i], *ne = ns + n, *ns1 = ns, *ne1 = ne - 1;
    while(ns < ne) {
        ns->v = i++;
        ns->next = ns+1;
        ns->prev = ns-1;
        ns++;
    }

    // for (int i = 1; i <= n; i++) {
    //     cur = &node_list[i];
    //     cur->v = i;
    //     cur->next = &node_list[i+1];
    //     cur->prev = &node_list[i-1];
    // }

    ns1->prev = ne1;
    ne1->next = ns1;
    //node_list[1].prev = &node_list[n];
    //node_list[n].next = &node_list[1];

    int mod = m;
    cur = &node_list[1];
    while(n) {
        if ((--mod) == 0) {
            mod = m;
            n--;
            cout << cur->v << " ";
            cur->next->prev = cur->prev;
            cur->prev->next = cur->next;
        }
        cur = cur->next;
    }


    return 0;
}

#endif