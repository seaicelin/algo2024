#include <iostream>

using namespace std;

#define MAXN 300

struct mystack{
    mystack():t(0){}
    void push(int v) {s[++t] = v;}
    void pop() {t--;}
    int top() {return s[t];}
    bool isEmpty() {return t == 0;}
    int t;
    char s[MAXN];
};

int main() {
    freopen("input.txt", "r", stdin);
    setbuf(stdout, NULL);

    mystack stack;

    char s;
    cin >> s;

    while(s != '@') {
        if (s == '(') stack.push(s);
        if (s == ')') {
            if (stack.isEmpty()) {
                cout << "NO";
                return 0;
            }
            stack.pop();
        }
        cin >> s;
    }
    if (stack.isEmpty()) cout << "YES";
    else cout << "NO";

    return 0;
}