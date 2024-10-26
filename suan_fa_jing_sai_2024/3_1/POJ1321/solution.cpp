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

const int maxn = 10;

char cell[maxn][maxn];
int row[maxn], col[maxn];
int n, k;

int ans,cur_row;

void dfs(int y, int v) {
    if (v == k) {
        ans++;
        return;
    }
    if (y == n+1) return;

    rep(x, 1, n) {
        // 当前层有可以放置的地方 ， 则选中然后递归下一层。
        if (cell[y][x] == '#' && col[x] == 0) {
            col[x] = 1;
            dfs(y+1, v+1);
            col[x] = 0;
        }
    }
    //如果这一行都没有可以放的地方，则递归下一层
    dfs(y+1, v);
}

void work() {
    while(true){
        cin >> n >> k;
        if (n == -1 || k == -1) return;
        rep(i, 1, n) {
        rep(j, 1, n) {
                cin >> cell[i][j];       
            }
        }

        rep(i, 1, n) row[i] = col[i] = 0;
        ans = 0;

        //从第一行开始放
        dfs(1, 0);


        log("%d\n", ans);
    }
}


}
void solve() {
    ice::work();
}