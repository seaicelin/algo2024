#include "main.h"
#if v10

#include <iostream>

using namespace std;

int main() {

    freopen("input.txt", "r", stdin);

    int n,m;
    cin >> n >> m;

    int a[100];
    for (int i = 0; i < n; i++) a[i] = i+1; 

    int cnt = 0;
    int mod = m;
    int size = n;
    while (n) {
        cnt %= size;
        if (a[cnt] == 0) {
            cnt++;
            continue;
        }
        mod--;
        if (mod == 0) {
            mod = m;
            n--;
            cout << a[cnt] <<" ";
            a[cnt] = 0;
        }
        cnt++;
    }

    return 0;
}
#endif