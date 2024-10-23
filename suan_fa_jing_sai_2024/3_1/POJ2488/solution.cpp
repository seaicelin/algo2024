#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;

#define DEBUG 0
#define rep(i, l, r) for(int i = (l); i <= (r); i++)
#define log(...) do{if(DEBUG) fprintf(fp, __VA_ARGS__); else printf(__VA_ARGS__);}while(0)

FILE* fp;

namespace ice{

const int maxn = 30;

//A1是在左下角啊，不是右上角

const int dx[8] = {-1, 1, -2, 2, -2, 2, -1, 1}; //1-8
const int dy[8] = {-2, -2, -1, -1, 1, 1, 2, 2}; //a-h

int n, p, q;//p 1-8. q a-h

int vis[maxn][maxn];
int ay[maxn], ax[maxn];
int cnt;
bool flag;

void init_vis() {
    rep(y, 0, maxn-1) rep(x, 0, maxn-1) vis[x][y] = 0;
}

void dfs(int x, int y, int step) {
    if (step == cnt) {
        flag = true;
        return;
    }

    rep(i, 0, 7) {
        int ny = y + dy[i];
        int nx = x + dx[i];
        if (ny <= 0||ny > q || nx <= 0 || nx > p) continue;
        if (vis[nx][ny] == 1) continue;
        if (flag == true) return;
        ax[step+1] = nx;
        ay[step+1] = ny;
        vis[nx][ny] = 1;
        dfs(nx, ny, step+1);
        vis[nx][ny] = 0;
    }
}

void work() {
    cin >> n;
    int t=0;
    while(n--) {
        t++;
        cin >> p >> q;//p 1-8,q a-h
        cnt = p*q;
        flag = false;
        init_vis();

        ax[1] = 1;//x;
        ay[1] = 1;//y;
        vis[1][1] = 1;
        dfs(1, 1, 1);

        log("Scenario #%d:\n", t);
        if (flag == false) {
            log("impossible\n");
        } else {
            rep(i, 1, cnt) {
                log("%c%d", ay[i]+'A'-1, ax[i]);
            }
            log("\n");
        }
        if (n != 0)log("\n");
    }
}


}
void solve() {
    ice::work();
}