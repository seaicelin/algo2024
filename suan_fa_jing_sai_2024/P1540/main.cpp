#include <stdio.h>

#define max_n 1001

struct Queue{
    Queue():front(0), tail(0) {
        for (int i = 0; i < max_n; i++) {
            vis[i] = 0;
        }
    }
    void push(int val) {
        vis[val] = 1;
        q[tail++] = val;
    }
    int pop() {
        vis[q[front]] = 0;
        return q[front++];
    }
    int size() {return tail - front;}
    int front;
    int tail;
    int q[max_n];
    int vis[max_n];
};

int main() {
    freopen("input.txt", "r", stdin);
    int m,n;
    scanf("%d %d", &m, &n);

    Queue q;

    int v;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        scanf("%d", &v);
        if(q.vis[v] == 0) {
            ans++;
            if(q.size() == m) {
                q.pop();
            }
            q.push(v);
        }
    }
    printf("%d\n", ans);
    return 0;
}