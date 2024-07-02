/*
用前缀和也可以
https://blog.csdn.net/wkyhnyq/article/details/130875484
*/

#include <iostream>
#include <stdio.h>

using namespace std;

#define MAX_SZ 1000005

struct QUEUE{
    QUEUE():f(0),t(0){}
    void push(int i) {
        q[t++]=i;
    }
    void popFront() {f++;}
    void popTail() {t--;}
    int front() {return q[f];}
    int tail() {return q[t-1];}
    bool isEmpty() {return f == t;}
    int f;
    int t;
    int q[MAX_SZ * 2];
};

int a[MAX_SZ * 2];

int main() {
    freopen("input.txt", "r", stdin);
    setbuf(stdout, NULL);
    int n,k;
    cin >> n;
    QUEUE Q;

    a[0]=0;

    int index = -1;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i+n] = a[i];
    }

    for (int i = 1; i <= 2*n; i++) {
        a[i] += a[i-1];
    }

    int ans = 0;
    Q.push(0);
    for (int i = 1; i <= 2*n - 1; i++) {
        while(!Q.isEmpty() && Q.front() <= i - n) {
            Q.popFront();
        }
        while(!Q.isEmpty() && a[Q.tail()] >= a[i]) {
            Q.popTail();
        }
        Q.push(i);
        if (i >= n && a[Q.front()] - a[i-n] >= 0) ans++;
    }

    cout << ans << endl;
    while(1);
    return 0;
}