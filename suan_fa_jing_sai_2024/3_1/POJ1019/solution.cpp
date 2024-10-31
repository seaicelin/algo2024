#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <math.h>
using namespace std;

#define DEBUG 1
#define rep(i, l, r) for(int i = (l); i <= (r); i++)
#define log(...) do{if(DEBUG) fprintf(fp, __VA_ARGS__); else printf(__VA_ARGS__);}while(0)

FILE* fp;

namespace ice{

const int maxn = 25;

struct Node{
    char s[100];
    int len;

    void operator=(const Node& node) {
        len = node.len;
        rep(i, 0, len-1) s[i] = node.s[i]; 
    }
};

Node node_list[maxn * 2];
int node_len;

int n;
char c;
bool vis[maxn*2];
int ans_len;
int max_len;
int dp[maxn*2][maxn*2];

int get_len(char* str) {
    int len = 0;
    while (*str != '\0') {
        str++;
        len++;
    }
    return len;
}

int is_ok(Node* cur, Node* pre) {
    bool ret = false;
    int len = -1;

    for (int i = 0; i < cur->len; i++) {
        if (pre->len <= i + 1) return len; 
        ret = true;
        for (int j = 0; j <= i; j++) {
            int pre_index = pre->len - i - 1 + j;
            if (cur->s[j] != pre->s[pre_index]) {
                ret = false;
            }    
        }
        if (ret) {
            len = i + 1;
            break;
        }
    }
    return len;
}

void dfs(int id) {

    if (max_len < ans_len) max_len = ans_len;

    Node *cur;
    int len;
    rep(i, 0, node_len-1) {
        if(vis[i])continue;

        cur = &node_list[i];

        len = dp[id][i];
        if (len == -1) continue;

        ans_len += (cur->len - len);
        vis[i] = true;
        dfs(i);
        vis[i] = false;
        ans_len -= (cur->len - len);
    }

}

void init() {
    for (int i = 0; i < node_len; i++) {
        for (int j = 0; j < node_len; j++) {
            dp[i][j] = is_ok(&node_list[j], &node_list[i]);
        }
    }
}

void work() {
    Node* node;
    node_len = 0;

    cin >> n;
    rep(i, 0, n-1) {
        node = &node_list[node_len++];
        cin >> node->s;
        node->len = get_len(node->s);
        node_list[node_len++] = *node;
    }
    cin >> c;

    init();
    rep(i, 0, n*2) vis[i] = false;
    max_len = 0;

    for (int i = 0; i < node_len; i+=2) {
        node = &node_list[i];
        if (c == node->s[0]) {
            ans_len += node->len;
            vis[i] = true;
            dfs(i);
            vis[i] = false;
            ans_len -= node->len;
        }
    }
    log("%d",max_len);
}


}
void solve() {
    ice::work();
}