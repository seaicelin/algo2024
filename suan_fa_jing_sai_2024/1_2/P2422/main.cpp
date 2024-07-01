/*
区间内感受值的总和可以通过 前缀和 求出。
区间内最小的感受值的求解可以转化，不去确定某个区间内的最小值，
而是 确定最小值之后去找区间, 最小值已知，那区间的内所有值都会 大于 它，
构造一个 递增的单调队列 ，
找到左右第一个比假设最小值小的，两个值之间的区间最小值即是假设的值。
https://www.cnblogs.com/Hamine/p/15229237.html
https://blog.csdn.net/qq_50332374/article/details/125832110
https://apro1066.top/2019/02/24/%E6%B4%9B%E8%B0%B7-P2422%20%E8%89%AF%E5%A5%BD%E7%9A%84%E6%84%9F%E8%A7%89/
*/

#include <stdio.h>
#include <iostream>

using namespace std;

#define MAXN 1000005

int stk[MAXN];
int l[MAXN];
int a[MAXN]={0};
int sum[MAXN]={0};
int top;

int main() {
    freopen("input.txt", "r", stdin);
    setbuf(stdout, NULL);
    top = 0;
    int n;
    cin >> n;
    a[++n]=0;
    for (int i = 1; i <= n; i++) {
        sum[i]=sum[i-1]+a[i];
        while(a[i] < a[stk[top]]) {
            l[i] += sum[i-1] - sum[stk[top]];
            top--;
        }
        l[i] = sum[i] - sum[stk[top]];
        stk[++top]=i;
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = std::max(ans, l[i]*a[i]);
    }
    cout << ans << endl;
    return 0;
}