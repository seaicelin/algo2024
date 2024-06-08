/*洛谷-P1160 队列安排*/
#include <stdio.h>

struct Node{
    int val;
    Node* prev;
    Node* next;
    Node():val(0),prev(nullptr),next(nullptr){}
};

int main() {
    freopen("input.txt", "r", stdin);
    int n;
    scanf("%d", &n);

    Node* head;
    Node n_list[n+1];
    n_list[1].val = 1;
    head = &n_list[1];
    int k, p;
    for (int i = 2; i <= n; i++) {
        scanf("%d %d", &k, &p);
        n_list[i].val = i;
        //right
        if (p == 1) {
            if (n_list[k].next) {
                n_list[k].next->prev = &n_list[i];
            }
            n_list[i].next = n_list[k].next;
            n_list[i].prev = &n_list[k];
            n_list[k].next = &n_list[i];
        }
        //left
        else {
            if (n_list[k].prev) {
                n_list[k].prev->next = &n_list[i];
            }
            n_list[i].next = &n_list[k];
            n_list[i].prev = n_list[k].prev;
            n_list[k].prev = &n_list[i];
            if (n_list[i].prev == nullptr) {
                head = &n_list[i];
            }
        }
    }

    int m;
    scanf("%d", &m);

    int v;
    for (int i = 0; i < m; i++) {
        scanf("%d", &v);
        Node* node = &n_list[v];
        if (node == head) {
            head = node->next;
            node->next = nullptr;
        } else {
            if (node->prev) {
                node->prev->next = node->next;
                //node->prev = nullptr;
            }
            if (node->next) {
                node->next->prev = node->prev;
                //node->next = nullptr;
            }
            node->next=node->prev=nullptr;
        }
    }

    while (head) {
        printf("%d ", head->val);
        head=head->next;
    }
    return 0;
}