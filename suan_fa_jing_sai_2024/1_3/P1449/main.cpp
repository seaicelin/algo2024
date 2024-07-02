#include <iostream>

using namespace std;

#define MAXN 100

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

    int a,b;
    int x = 0;
    mystack stack;

    char s;
    std::cin >> s;
    while(s != '@') {
        if (s >= '0' && s <= '9') {
            x *= 10;
            x += (s - '0');
        } else {
            if (s == '.') {
                stack.push(x);
                x = 0;
            } else if (s == '*') {
                a = stack.top(); stack.pop();
                b = stack.top(); stack.pop();
                stack.push(a*b);
            } else if (s == '+') {
                a = stack.top(); stack.pop();
                b = stack.top(); stack.pop();
                stack.push(a+b);
            } else if (s == '-') {
                a = stack.top(); stack.pop();
                b = stack.top(); stack.pop();
                stack.push(b-a);
            } else if (s == '/') {
                a = stack.top(); stack.pop();
                b = stack.top(); stack.pop();
                stack.push(b/a);
            }
        }
        std::cin >> s;
    }
    cout << stack.top();
    return 0;
}