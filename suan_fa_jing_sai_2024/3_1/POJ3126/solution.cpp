#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;

#define DEBUG 1
#define rep(i, l, r) for(int i = (l); i <= (r); i++)
#define rrep(i, r, l) for (int i = (r); i >= (l); i--)
#define log(...) do{if(DEBUG) fprintf(fp, __VA_ARGS__); else printf(__VA_ARGS__);}while(0)

FILE* fp;

namespace ice{

const int maxn = 1e4;
const int dx[4] = {1, 10, 100, 1000};

struct Node{
    int x;
    int s;
};

int t;
int src,dst;

int a[4];
Node q[maxn];
bool vis[maxn];
int front, tail;

bool is_prime(int x) {
    rep(i, 2, x/i) {
        if (x % i == 0) return false;
    }
    return true;
}

void work() {
    cin >> t;
    rep(i, 1, t) {
        cin >> src >> dst;

        rep(v,0,maxn-1) vis[v]=false;

        front = tail = 0;
        q[tail].x = src;
        q[tail++].s = 0;
        vis[src] = true;

        while (front < tail) {
            Node t = q[front++];

            if (t.x == dst) {
                log("%d\n", t.s);
                break;
            }

            rep(k, 0, 3) a[k] = t.x/dx[k]%10;

            rrep(k, 3, 0) {
                rep(m, 0, 9) {
                    if (a[k] == m) continue;
                    if (k == 3 && m == 0) continue;
                    int d=0;
                    rrep(j, 3, 0) {
                        if (j == k) {
                            d+= m*dx[j];
                        }
                        else { d += (a[j]*dx[j]);}
                    }
                    if (vis[d]) continue;
                    vis[d] = true;
                    if (is_prime(d)) {
                        q[tail].x = d;
                        q[tail++].s = t.s + 1;
                    }
                }

            }
        }
    }
}


}
void solve() {
    ice::work();
}