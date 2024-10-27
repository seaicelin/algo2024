#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;

#define DEBUG 1
#define rep(i, l, r) for(int i = (l); i <= (r); i++)
#define rrep(i, r, l) for(int i = (r); i >= (l); i--)
#define log(...) do{if(DEBUG) fprintf(fp, __VA_ARGS__); else printf(__VA_ARGS__);}while(0)

FILE* fp;

namespace ice{

const int maxn = 100000;

struct Node{
    int pre;
    int dir;
    int a;
    int b;
    int k;
    Node() {
        pre = dir = -1;
        a = b = k = 0;
    }
    void set(int pre_, int dir_,
        int a_, int b_, int k_) {
        pre = pre_;
        dir =dir_;
        a = a_;
        b = b_;
        k = k_;
    }
    void print() {
        log("pre=%d,dir=%d,a=%d,b=%d,k=%d\n",
            pre, dir, a, b, k);
    }
};

Node q[maxn];
int front, tail;
Node step[maxn];
int step_len;
bool vis[101][101][3][3];
int arr[3],c;
int a, b;

void init_vis() {
    rep(i, 0, 100) rep(j, 0, 100) rep(k, 0, 2) rep(m, 0, 2) vis[i][j][k][m] = false;
}

void work() {
    cin >> arr[1] >> arr[2] >> c;
    
    init_vis();

    front = tail = 0;
    q[tail].set(-1, -1, 0, 0, 0);
    tail++;

    while(front < tail) {
        Node t = q[front++];
        if (t.a == c || t.b == c) {
            step_len = 0;
            Node tar = t;
            while(tar.pre != -1) {
                step[step_len++] = tar;
                tar = q[tar.pre];
            }
            log("%d\n", step_len);
            rrep(j, step_len - 1, 0) {
                int k = step[j].k;
                if (step[j].dir == 1) {
                    log("FILL(%d)\n", k);
                } else if(step[j].dir == 2) {
                    log("DROP(%d)\n", k);
                } else {
                    log("POUR(%d,%d)\n", k, k == 1? 2:1);
                }
            }
            return;
        }
        rep(k, 1, 2){
            rep(i, 1, 3) {
                if (i == 1) {//full
                    if (k == 1) {
                        a = arr[1];
                        b = t.b;
                    } else {
                        a = t.a;
                        b = arr[2];
                    }
                }
                if (i == 2) {
                    if (k == 1) {
                        a = 0;
                        b = t.b;
                    } else {
                        a = t.a;
                        b = 0;
                    }
                }
                if (i == 3) {
                    a = t.a;
                    b = t.b;
                    if (k == 1) {
                        int d = arr[2] - b;
                        if (a >= d) {
                            a -= d;
                            b = arr[2];
                        } else {
                            b += a;
                            a = 0;
                        }
                    } else {
                        int d = arr[1] - a;
                        if (b >= d) {
                            b -= d;
                            a = arr[1];
                        } else {
                            a += b;
                            b = 0;
                        }
                    }
                }
                if (vis[a][b][k][i]) continue;
                vis[a][b][k][i] = true;
                q[tail].set(front-1, i, a, b, k);
                tail++;
            }
        }
    }
    log("impossible\n");
}
}

void solve() {
    ice::work();
}