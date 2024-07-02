/*
https://www.cnblogs.com/skl-hray/p/7643751.html
*/

#include <iostream>

using namespace std;

#define MAXN 110

struct NODE{
    int type;//char 0, int 1
    int data;
    NODE* next;
    NODE* prev;
    NODE():type(0),data(0),next(nullptr),prev(nullptr){}
};

NODE node_list[MAXN];
int node_cnt;

void initNodeList() {
    node_cnt = 0;
}

struct mystack{
    mystack():t(0){}
    void push(char c) {s[++t]=c;}
    char top() {return s[t];}
    void pop() {t--;}
    bool isEmpty() {return t == 0;}
    int t;
    char s[MAXN];
};

int getLevel(char c) {
    if (c == '^') return 5;
    if (c == '*' || c == '/') return 4;
    if (c == '+' || c == '-') return 3;
    if (c == '(') return 2;
    if (c == ')') return 1;
    return 0;
}

int cal(int a, int b, char c) {
    if (c == '-') return a - b;
    if (c == '+') return a + b;
    if (c == '*') return a * b;
    if (c == '/') return a / b;
    if (c == '^') {
        int tmp = a;
        if (b == 0) return 1;
        if (b == 1) return a;
        for (int i = 1; i < b; i++) {
            a *= tmp;
        }
        return a;
    }
    return 0;
}

void handleNodeList(int id) {
    NODE* node = &node_list[id];
    NODE *a, *b;
    b = node->prev;
    a = b->prev;
    char op = node->data;

    a->data = cal(a->data, b->data, op);
    a->next = node->next;
    if (node->next) node->next->prev = a;
}

void output() {
    NODE* node = &node_list[0];
    while(node) {
        if (node->type == 0) {
            cout << (char)node->data << " ";
        } else {
            cout << node->data << " ";
        }
        node = node->next;
    }
    cout << endl;
}

int main() {
    freopen("input.txt", "r", stdin);
    setbuf(stdout, NULL);

    mystack sd, sc;

    char c;
    while(cin >> c) {
        if (c >= '0' && c <= '9') {
            sd.push(c);
        } else {
            if (sc.isEmpty() || c == '(') {
                sc.push(c);
                continue;
            }
            if (c == ')') {
                while(sc.top() != '(') {
                    sd.push(sc.top());
                    sc.pop();
                }
                sc.pop();
                continue;
            }
            int sc_le = getLevel(sc.top());
            int c_le = getLevel(c);
            if (sc_le == c_le && c_le == 5) {
                sc.push(c);
                continue;
            }
            if (sc_le < c_le) {
                sc.push(c);
            } else {
                while(sc_le >= c_le) {
                    sd.push(sc.top());
                    sc.pop();
                    sc_le = getLevel(sc.top());
                }
                sc.push(c);
            }
        }
    }
    while(!sc.isEmpty()) {
        sd.push(sc.top());
        sc.pop();
    }

    initNodeList();

    int sclist[MAXN];
    int scCnt = 0;

    NODE* node;
    int h = 1;
    while(h <= sd.t) {
        c = sd.s[h];
        cout << c << " ";
        node = &node_list[node_cnt];
        if (c >= '0' && c <= '9') {
            node->data = c - '0';
            node->type = 1;
        } else {
            node->data = c;
            node->type = 0;
            sclist[scCnt++] = node_cnt;
        }
        h++;
        node_cnt++;
    }
    cout << endl;

    for (int i = 1; i < node_cnt; i++) {
        node_list[i].next = &node_list[i+1];
        node_list[i].prev = &node_list[i-1];
    }
    node_list[0].next = &node_list[1];
    node_list[node_cnt-1].next = nullptr;

    int index=0;
    while(index < scCnt) {
        int id = sclist[index];
        handleNodeList(id);
        output();
        index++;
    }
    return 0;
}