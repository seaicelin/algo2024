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

const int maxn = 15;

int n, sum;
int dp[maxn][maxn];
bool vis[maxn];
int ans[maxn];
bool mark;

void dfs(int k, int s) {
    if (k == n) {
        if (s == sum) {
            rep(j, 1, k) {
                mark = true;
                log("%d ", ans[j]);
            }
        }
        return;
    }

    rep(i, 1, n) {
        if (mark) return;
        if (vis[i]) continue;
        int s2 = s + (i) * dp[n][k+1];
        if (s2 > sum) continue;

        ans[k+1] = i;
        vis[i] = true;
        dfs(k+1, s2);
        vis[i] = false;
    }
}

void work() {
    cin >> n >> sum;
    
    rep(i, 1, n) vis[i] = false;

    dp[0][1]=1;
    rep(i, 1, n) {
        rep(j, 1, i) {
            dp[i][j] = dp[i-1][j-1] + dp[i-1][j];
        }
    }

    mark = false;
    dfs(0, 0);
}


}
void solve() {
    ice::work();
}