#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;

/*
https://www.cnblogs.com/thmyl/p/7456597.html
换一个角度看问题，如果我们穷举一个最小值a[i],然后往左右扩展，显然是对的，
复杂度 O(n^2)。所以我们要优化一下这个扩展过程。
首先扩展这个过程的原则就是所有加入这个区间的数都必须小于选定的最小值 a[i]，
那么我们可以把扩展过程换一个叙述方法，就是对于每个数我们分别往左右找到第一个比 a[i]小的数，
编号分别记成 l[i]、r[i]，则答案就是 sum(l[i]+1,r[i]-1)*×a[i]。

那么这两个数怎么求呢？可以正着跑一遍单调栈，再翻着跑一遍单调栈，再用前缀和搞一下就行了。
时间复杂度 O(n)O(n)。
*/

#define DEBUG 0
#define rep(i, l, r) for(int i = (l); i <= (r); i++)
#define rrep(i, r, l) for(int i = (r); i >= (l); i--)
#define log(...) do{if(DEBUG) fprintf(fp, __VA_ARGS__); else printf(__VA_ARGS__);}while(0)

FILE* fp;

namespace ice{

typedef long long ll;
const int maxn = 1e5+10;

int n;
ll arr[maxn];
int st[maxn],l[maxn],r[maxn];
ll sum[maxn];
int t;

void work() {
    sum[0] = 0;
    cin >> n;
    rep(i, 1, n) {
        cin >> arr[i]; 
        sum[i] = sum[i-1] + arr[i];
    }

    t = 0;
    rep(i, 1, n) {
        while(t > 0 && arr[i] < arr[st[t]]) {
            r[st[t]] = i;
            //log("r[%d]=%d\n", st[t], i);
            --t;
        }
        st[++t] = i;
        r[i] = n+1;
        //log("r[%d]=%d\n", st[t], r[i]);
    }
    t = 0;
    rrep(i, n, 1) {
        while(t > 0 && arr[i] < arr[st[t]]) {
            l[st[t]] = i;
            //log("l[%d]=%d\n", st[t], i);
            --t;
        }
        st[++t] = i;
        l[i]=0;
        //log("l[%d]=%d\n", st[t], i-1);
    }
    ll ans = 0;
    rep(i, 1, n) {
        ans = max(ans, (sum[r[i]-1] - sum[l[i]])*arr[i]);
    }
    log("%lld\n", ans);
}


}
void solve() {
    ice::work();
}