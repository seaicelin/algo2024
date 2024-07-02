/*
1、getline(cin,str)读取换行符 并且将换行符替换成'\0'，并将换行符从输入队列中抹去。
2、cin不会读入换行符；//这个总所周知，但是可以利用这个特点来连续读入任意个字符串。
3、cin.getline(char*,len)读取换行符并替换成'\0'，并将换行符从输入队列中抹去
*/

#include <iostream>

using namespace std;

#define MAXN 1010

struct mystack{
    mystack():t(0){}
    void push(char c){
        s[++t]=c;
    }
    char top(){return s[t];}
    void pop() {t--;}
    bool ie() {return t == 0;}
    void reset() {t=0;}
    int t;
    char s[MAXN];
};

void solution_v10() {
    freopen("input.txt", "r", stdin);
    setbuf(stdout, NULL);

    int n;
    cin >> n;
    getchar();
    mystack stack;

    char c_str[MAXN];
    for (int i = 0; i < n; i++) {
        std::cin.getline(c_str,MAXN);
        stack.reset();
        for (int j = 0; j < MAXN; j++) {
            if (c_str[j] == ' ' || c_str[j] == '\0') {
                while(!stack.ie()) {
                    cout << stack.top();
                    stack.pop();
                }
                cout << ' ';
                if (c_str[j] == '\0') break;
                continue;
            }
            stack.push(c_str[j]);
        }
        cout << endl;
    }
}

int main() {
    solution_v10();
    while(1);
    return 0;
}