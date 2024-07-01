/*
最大子序列和
https://www.cnblogs.com/ECJTUACM-873284962/p/7219912.html
*/
#include <stdio.h>

#define MAX_SZ 100005


int a[MAX_SZ];
int dp[MAX_SZ];

int main() {
    freopen("input.txt", "r", stdin);
    setbuf(stdout, NULL);
    int tc;
    scanf("%d", &tc);

    for (int i = 0; i < tc; i++)  {
        int n;
        scanf("%d", &n);
        for (int j = 0; j < n; j++) {
            scanf("%d", &a[j]);
        }
        int startIndex, endIndex, tempIndex;
        startIndex = endIndex = tempIndex = 0;
        int max_sum = a[0];
        dp[0] = a[0];
        for (int j = 1; j < n; j++) {
            if (dp[j-1] >= 0) {
                dp[j] = dp[j-1] + a[j];
            } else {
                dp[j] = a[j];
                tempIndex = j;
            }
            if (max_sum < dp[j]) {
                max_sum = dp[j];
                startIndex = tempIndex;
                endIndex = j;
            }
        }
        printf("Case %d:\n", i+1);
        printf("%d %d %d\n", max_sum, startIndex+1, endIndex+1);
        printf("\n");
    }

}