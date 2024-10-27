#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;

#define DEBUG 1
#define rep(i, l, r) for(int i = (l); i <= (r); i++)
#define log(...) do{if(DEBUG) fprintf(fp, __VA_ARGS__); else printf(__VA_ARGS__);}while(0)

FILE* fp;

namespace ice{

const int maxn = 2e5+10;

struct Node {
    int x;
    int step;
    Node(){x = step = 0;}
};

int n, k;
bool vis[maxn];
Node q[maxn];
int front,tail;
int ans;
void work() {
    cin >> n >> k;

    rep(i, 0, maxn-1) vis[i] = false;

    front = tail = 0;
    q[tail].x = n;
    q[tail++].step = 0;
    vis[n] = true;

    while (front < tail) {
        Node t = q[front++];

        if (t.x == k) {
            log("%d\n", t.step);
            return;
        }

        int nx;
        rep(i, 1, 3) {
            if (i == 1) {
                nx = t.x+1;
            }
            if (i == 2) {
                nx = t.x - 1;
            }
            if (i == 3) {
                nx = t.x*2;
            }
            if (nx > 1e5 || nx < 0) continue;
            if (vis[nx]) continue;
            q[tail].x = nx;
            q[tail++].step = t.step + 1;
            vis[nx] = true;
        }
    }
}


}
void solve() {
    ice::work();
}