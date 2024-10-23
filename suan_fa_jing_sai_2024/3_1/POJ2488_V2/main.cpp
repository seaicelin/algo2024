#include <cstdio>
#include <cstring>

const int maxn = 50;
const int dx[8] = {-1, 1, -2, 2, -2, 2, -1, 1}; //A-H
const int dy[8] = {-2, -2, -1, -1, 1, 1, 2, 2}; //1-8

int n, p, q, cnt;//p 1-8. q a-h

bool vis[maxn][maxn];
int ay[maxn*maxn], ax[maxn*maxn];

bool is_ok(int x, int y) {
    return x > 0 && x <= p && y > 0 && y <= q
        && !vis[x][y];
}

bool dfs(int x, int y, int step) {
    if (step == cnt) return true;

    for (int i = 0; i < 8; i++) {
        int ny = y + dy[i];
        int nx = x + dx[i];
        if (is_ok(nx, ny)) {
            ax[step+1] = nx;
            ay[step+1] = ny;
            vis[nx][ny] = true;
            if(dfs(nx, ny, step+1)) return true;
            vis[nx][ny] = false;
        }
    }
    return false;
}

void work() {
    scanf("%d", &n);
    for (int t = 1; t <= n; t++){
        scanf("%d %d", &p, &q);//p 1-8. q a-h
        cnt = p*q;
        //init_vis();
        memset(vis, false, sizeof(vis));
        ax[1] = 1;//x;
        ay[1] = 1;//y;
        vis[1][1] = true;
        bool flag = dfs(1, 1, 1);

        printf("Scenario #%d:\n", t);
        if (flag == false) {
            printf("impossible\n");
        } else {
            for (int i = 1; i <= cnt; i++){
                printf("%c%d", ay[i]+'A'-1, ax[i]);
            }
            printf("\n");
        }
        if (n != t)printf("\n");
    }
}

int main() {

    freopen("input.txt","r",stdin);
    setbuf(stdout, NULL);

    work();

    return 0;
}