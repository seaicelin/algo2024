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

const int maxn = 100;

int n;
int cell[maxn][maxn];
int col[maxn], row[maxn];
int tx[maxn];
int cnt;

bool is_ok (int x, int y) {
    return x >= 1 && x <= n && y >= 1 && y <= n;
}

bool is_can_put(int x, int y) {
    int nx, ny;
    // nx = x; ny = y;
    // while(is_ok(nx, ny)) {
    //     if (cell[ny][nx] != 0) return false;
    //     nx += 1;
    //     ny += 1;
    // }
    nx = x; ny = y;
    while(is_ok(nx, ny)) {
        if (cell[ny][nx] != 0) return false;
        nx -= 1;
        ny -= 1;
    }
    // nx = x; ny = y;
    // while(is_ok(nx, ny)) {
    //     if (cell[ny][nx] != 0) return false;
    //     nx -= 1;
    //     ny += 1;
    // }

    nx = x; ny = y;
    while(is_ok(nx, ny)) {
        if (cell[ny][nx] != 0) return false;
        nx += 1;
        ny -= 1;
    }
    return true;
}

void dfs(int y, int s) {
    if (s == n) {
        cnt++;
        if (cnt > 3) 
            return;
        rep(i, 0, n-1) {
            log("%d ", tx[i]);
        }
        log("\n");
    }
    if (y > n) return;
    rep(x, 1, n) {
        if (cell[y][x] != 0) continue;
        if (col[x] || row[y]) continue;
        if (!is_can_put(x, y)) continue;
        tx[s] = x;
        col[x] = row[y] = 1;
        cell[y][x] = x;
        dfs(y+1, s+1);
        cell[y][x] = 0;
        col[x] = row[y] = 0;        
    }
}

void work() {
    cin >> n;

    rep (i, 0, maxn-1) col[i] = row[i] = tx[i] = 0;

    rep(i, 0, maxn - 1) rep(j, 0, maxn - 1) cell[i][j] = 0;

    cnt = 0;
    dfs(1, 0);
    log("%d\n",cnt);
}


}
void solve() {
    ice::work();
}