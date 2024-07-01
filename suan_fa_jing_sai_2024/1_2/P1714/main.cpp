#include <iostream>
#include <stdio.h>
#include <algorithm>

using namespace std;

#define MAX_SZ 500010

// struct NODE{
//     int val;
//     int ind;
//     NODE():val(0), ind(0){}
// };

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
    int q[MAX_SZ];
};

int a[MAX_SZ];

int main() {
    freopen("input.txt", "r", stdin);
    setbuf(stdout, NULL);
    int n,k;
    cin >> n >> k;
    a[0]=0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i]+=a[i-1];
    }

    QUEUE Q;
    Q.push(0);
    int max_value = -2e9;
    for (int i = 1; i <= n; i++) {
        max_value = std::max(a[i]-a[Q.front()], max_value);
        while(!Q.isEmpty() && Q.front() <= i - k) {
            Q.popFront();
        }
        while(!Q.isEmpty() && a[Q.tail()] >= a[i]) {
            Q.popTail();
        }
        Q.push(i);

    }
    cout << max_value << endl;
    while(1);
    return 0;
}