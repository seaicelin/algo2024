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

const int maxn = 25;

//up,right,down,left
const int dx[4] = {0, 1, 0, -1};
const int dy[4] = {-1,0, 1, 0};

int cell[maxn][maxn];

int h, w;
int sx, sy, ex, ey;
int ans, max_ans;

bool is_ok(int x, int y) {
    return x >= 1 && x <= w && y >= 1 && y <= h;
}

void dfs(int x, int y, int step) {
    if (step >= max_ans || step > 10) {
        return;
    }
    if (x == ex && ey == y) {
        if (max_ans > step) {
            max_ans = step;
        }
        return;
    }

    rep(i, 0, 3) {
        bool ret = false;
        bool mark = false;
        int nx = x;
        int ny = y;
        while(true) {
            nx += dx[i];
            ny += dy[i];
            if (!is_ok(nx, ny)) break;
            if (cell[ny][nx] == 0 || cell[ny][nx] == 2) {mark = true; continue;}
            if (cell[ny][nx] == 3) {
                if (max_ans >= step + 1) max_ans = step+1;
                return;
            }
            if (cell[ny][nx] == 1) {
                if (mark == true)
                    ret = true;
                break;
            }
        }
        if (ret == true) {
            cell[ny][nx] = 0;
            dfs(nx-dx[i], ny-dy[i], step+1);
            cell[ny][nx] = 1;
        }
    }
}

void work() {
    while (true){
        cin >> w >> h;
        if (w == 0 || h == 0) return;

        rep(y, 1, h) {
            rep(x, 1, w) {
                cin >> cell[y][x];
                if (cell[y][x] == 2) {
                    sx = x;
                    sy = y;
                }
                if (cell[y][x] == 3) {
                    ex = x;
                    ey = y;
                }
            }
        }

        max_ans = 1000000000;
        dfs(sx, sy, 0);
        if (max_ans <= 10) {
            log("%d\n", max_ans);
        } else log("%d\n", -1);
    }
}


}
void solve() {
    ice::work();
}