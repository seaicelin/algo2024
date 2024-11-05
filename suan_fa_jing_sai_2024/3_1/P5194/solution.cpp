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
    
const int maxn = 1010;

int n, c;
int arr[maxn];
long long sum[maxn];
long long max_c;

void dfs(int k, long long s) {
    if (k <= 0) {
        max_c = std::max(max_c, s);
        return;
    }
    if (s + sum[k] <= c) {
        max_c = std::max(max_c, s + sum[k]);
        return;
    }
    if (s + arr[k] <= c) {
        dfs(k-1, s + arr[k]);
    }
    dfs(k-1, s);
}

void work() {

    sum[0] = 0;
    max_c = 0;

    cin >> n >> c;
    rep(i, 1, n) {
        cin >> arr[i]; 
        sum[i] = sum[i-1] + arr[i];
    }

    dfs(n, 0);
    log("%lld", max_c);
}


}
void solve() {
    ice::work();
}