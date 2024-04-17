#include <stdio.h>
#include <algorithm>

#define INF 0x7FFFF

int main() {

    int w = 15;

    int f[105],n,cost;

    f[0] = 0;
    //从1开始dp
    //最有子结构 无后效性
    for (int i = 1; i <= w; i++) {
        cost = INF;
        if (i - 1 >= 0) cost = std::min(cost, f[i-1] + 1);
        if (i - 5 >= 0) cost = std::min(cost, f[i-5] + 1);
        if (i - 11 >= 0) cost = std::min(cost, f[i-11] + 1);
        f[i] = cost;
        printf("i=%d, f[%d] = %d\n", i, i, f[i]);
    }

    return 0;
}