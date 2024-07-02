#include <iostream>

using namespace std;

#define MAXN 100005

int a[MAXN];
int ans[MAXN];
int cnt;

struct mystack{
    mystack():t(0){}
    void push(int v) {s[++t] = v;}
    void pop() {t--;}
    int top() {return s[t];}
    bool isEmpty() {return t == 0;}
    int t;
    int s[MAXN];
};

int main() {
    freopen("input.txt", "r", stdin);
    setbuf(stdout, NULL);

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    mystack s;
    cnt = 1;
    for (int i = n; i >= 1; i--) {
        while(!s.isEmpty() && a[s.top()] <= a[i]) s.pop();
        if (s.isEmpty()) ans[cnt++]=0;
        else ans[cnt++]=s.top();
        s.push(i);
    }

    for (int i = n; i>=1; i--) {
        cout << ans[i] << endl;
    }

    return 0;
}