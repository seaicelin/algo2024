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

const int maxn = 35;

const int dx[6] = {-1, 1, 0, 0, 0, 0};
const int dy[6] = {0, 0, -1, 1, 0, 0};
const int dz[6] = {0, 0, 0, 0, -1, 1};

struct Node{
    int x,y,z,s;
    inline void set(int x_, int y_, int z_, int s_) {
        x = x_;
        y = y_;
        z = z_;
        s = s_;
    }
};

int l,r,c;

char cell[maxn][maxn][maxn];
bool vis[maxn][maxn][maxn];

Node q[maxn*maxn*maxn];
int front, tail;

Node sn,en;
bool mark;
int nx, ny, nz;

bool is_ok(int x, int y, int z) {
    return x >= 1 && x <= c &&
            y >= 1 && y <= r &&
            z >= 1 && z <= l;
}

void work() {
    while(true) {
        cin >> l >> r >> c;
        if (l == 0 && r == 0 && c == 0) return;

        rep(i, 1, l) rep(j, 1, r) rep(k, 1, c) { 
            vis[i][j][k] = false;
            cin >> cell[i][j][k];
            if (cell[i][j][k] == 'S') {
                sn.set(k, j, i, 0);
            }
            if (cell[i][j][k] == 'E') {
                en.set(k, j, i, 0);
            }
        }

        front = tail = 0;
        q[tail++] = sn;
        vis[sn.z][sn.y][sn.x] = true;

        mark = false;
        while (front < tail && mark == false) {
            Node top = q[front++];
            rep(i, 0, 5) {
                nx = top.x + dx[i];
                ny = top.y + dy[i];
                nz = top.z + dz[i];
                if (!is_ok(nx, ny, nz)) continue;
                if (vis[nz][ny][nx]) continue;
                if (cell[nz][ny][nx] == '#') continue;
                if (cell[nz][ny][nx] == 'E') {
                    log("Escaped in %d minute(s).\n", top.s + 1);
                    mark = true;
                    break;
                }
                vis[nz][ny][nx] = true;
                q[tail++].set(nx, ny, nz, top.s+1);
            }
        }

        if (mark == false) log("Trapped!\n");
    }
}


}
void solve() {
    ice::work();
}