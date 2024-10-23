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

//S 1, E 2, # -1, . 0

const int maxn = 50;

const int dy[4]={-1, 0, 1, 0};
const int dx[4]={0, 1, 0, -1};
const int UP = 0;
const int RIGHT = 1;
const int DOWN = 2;
const int LEFT = 3;

const int dy2[4]={-1, 0, 1, 0};
const int dx2[4]={0, -1, 0, 1};
const int UP2 = 0;
const int LEFT2 = 1;
const int DOWN2 = 2;
const int RIGHT2 = 3;


int n, h, w;
int cell[maxn][maxn];
bool vis[maxn][maxn];

int sx,sy;
int ex,ey;
int ans_left, ans_right, ans_bfs;

struct Node{
    int x,y;
    int step;
};

struct my_queue{
    my_queue() {reset();}
    void pop() {front++;}
    Node top() {return q[front];}
    void push(int x, int y, int s) {
        q[tail].step = s;
        q[tail].x = x;
        q[tail++].y = y;
    }
    bool isEmpty() {return front == tail;}
    void reset() {front = tail = 0;}
    int front;
    int tail;
    Node q[maxn * maxn + 10];
};

my_queue queue;

void init_vis() {
    rep(y, 0, maxn-1) rep(x, 0, maxn - 1) vis[y][x] = false;
}

void init_cell(){
    rep(y, 0, maxn-1){
        rep(x, 0, maxn-1) {
            cell[y][x] = -1;
        }
    }
}

bool is_ok(int x, int y) {
    return x>=1 && x <= w && y >= 1 && y <= h;
}

bool dfs_right(int x, int y, int step, int cur_dir) {
    if (x == ex && y == ey) {
        ans_right = step;
        return true;
    }
    rep(i, 0, 3) {
        int dir = (cur_dir + i + 3)%4;
        int ny = y + dy2[dir];
        int nx = x + dx2[dir];
        if (is_ok(nx, ny) && cell[ny][nx] != -1)
            if(dfs_right(nx, ny, step+1, dir)) return true;
    }
    return false;
}

bool dfs_left(int x, int y, int step, int cur_dir) {
    if (x == ex && y == ey) {
        ans_left = step;
        return true;
    }
    rep(i, 0, 3) {
        int dir = (cur_dir + i + 3)%4;
        int ny = y + dy[dir];
        int nx = x + dx[dir];
        if (is_ok(nx, ny) && cell[ny][nx] != -1){
            if(dfs_left(nx, ny, step+1, dir)) return true;
        }
    }
    return false;
}

void bfs(int x, int y) {
    init_vis();

    while(!queue.isEmpty()) {
        Node top = queue.top(); queue.pop();
        rep(i, 0, 3) {
            int ny = top.y + dy[i];
            int nx = top.x + dx[i];
            if (!is_ok(nx, ny)) continue;
            if (vis[ny][nx]) continue;
            if (cell[ny][nx] == -1) continue;
            if (ny == ey && nx == ex) {
                ans_bfs = top.step + 1;
                return;
            }
            vis[ny][nx] = true;
            queue.push(nx, ny, top.step + 1);
        }
    }
}

void work() {
    cin >> n;
    rep(t, 1, n) {
        ans_left = ans_right = ans_bfs = 0;
        init_cell();
        cin >> w >> h;
        rep(y, 1, h) {
            rep(x, 1, w) {
                char c;
                cin >> c;
                if (c == '#') cell[y][x] = -1;
                if (c == '.') cell[y][x] = 0;
                if (c == 'S') cell[y][x] = 1, sx = x, sy = y;
                if (c == 'E') cell[y][x] = 2, ex = x, ey = y;
            }
        }

        dfs_left(sx, sy, 1, 0);
        dfs_right(sx, sy, 1, 0);

        queue.reset();
        queue.push(sx, sy, 1);
        bfs(sx,sy);
        log("%d %d %d\n", ans_left, ans_right, ans_bfs);
    }
}

}
void solve() {
    ice::work();
}