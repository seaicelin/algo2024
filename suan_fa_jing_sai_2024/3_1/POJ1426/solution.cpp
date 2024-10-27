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

const int maxn = 1e6;

long long q[maxn];

int n;
bool flag;

void dfs(long long ans, int step) {
    if(step > 19 || flag) return;
    if (ans % n == 0) {
        log("%lld\n", ans);
        flag = true;
        return;
    }

    dfs(ans*10+1, step+1);
    dfs(ans*10, step+1);
}

void work() {
    while(cin >> n && n) {
        // flag=false;
        // dfs(1,1);
        int front, tail;
        front = tail = 0;
        q[tail++] = 1;
        while(front < tail) {
            long long t = q[front++];
            if (t % n == 0) {
                log("%lld\n", t);
                break;
            }
            q[tail++] = t*10;
            q[tail++] = t*10+1;
        }
    }
}


}
void solve() {
    ice::work();
}