#include <iostream>

using namespace std;

#define MAXN 1000005

struct mystack{
    mystack():t(0){}
    void push(int v) {s[++t] = v;}
    void pop() {t--;}
    long long top() {return s[t];}
    bool isEmpty() {return t == 0;}
    int t;
    long long s[MAXN];
};

void solution_v10() {
    freopen("input.txt", "r", stdin);
    setbuf(stdout, NULL);

    mystack stack;

    bool flag = false;
    long long a, x;
    x = 0;
    char s;
    while(cin >> s) {
        if (s >= '0' && s <= '9') {
            x *= 10; x += (s-'0');
        } else {
            x %= 10000;
            if (flag == true) {
                flag = false;
                a = stack.top(); stack.pop();
                x*=a;
            }
            if (s == '*') {
                flag = true;
            }
            x %= 10000;
            stack.push(x);
            x = 0;
        }
    }
    if (flag == true) {
        flag = false;
        a = stack.top(); stack.pop();
        x *= a;
    }
    x %= 10000;
    stack.push(x);

    x = 0;
    while(!stack.isEmpty()) {
        x += stack.top();
        stack.pop();
    }

    cout << x % 10000;
}


int main() {
    solution_v10();
    while(1);
    return 0;
}