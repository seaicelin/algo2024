#include <iostream>
#include <stdio.h>
using namespace std;


const int maxn = 10005;
const int maxe = 50005*2;
const int inf = 1000000005;


struct Node {
    int u;
    int f;
    int head;
    Node() {u = f = head = 0;}
};

struct Edge {
    int u;
    int v;
    int c;
    int next;
    Edge() {u=v=c=next=0;}
}; 

Node node[maxn];
Edge edge[maxe];
bool vis[maxn];

int n,m,b,bb;
bool flag;

void dfs(int s, int d, int mid) {

    //if (node[s].f > mid) return;
    if (b < 0) return;
    //if (vis[s]) return;
    if (flag == true) return;

    if (s == d) {
        flag = true;
        return;
    }

    int i, to, c;
    for (i = node[s].head; i; i = edge[i].next) {
        to = edge[i].v;
        c = edge[i].c;
        if (vis[to])continue;
        if (node[to].f > mid) continue;
        vis[to]=true;
        b-=c;
        dfs(to, n, mid);
        b+=c;
        vis[to]=false;
    }
}

bool check(int mid) {
    flag = false;
    dfs(1, n, mid);
    if (flag) return true;
    return false;
}

int main() {
    freopen("input.txt","r",stdin);
    setbuf(stdout, NULL);

    int left,right;
    left = inf;
    right = 0;

    cin>>n>>m>>bb;

    int f;
    for (int i = 1; i <= n; i++) {
        cin >> f;
        node[i].u = i;
        node[i].f = f;
        if (left > f) left = f;
        if (right < f) right = f;
    }

    right++;

    int from,to,c;
    int cnt = 0;
    Edge* pe;
    for (int i = 1; i <= m; i++) {
        cin >> from >> to >> c;
        pe = &edge[++cnt];
        pe->u = from;
        pe->v = to;
        pe->c = c;
        pe->next = node[from].head;
        node[from].head = cnt;
    
        pe = &edge[++cnt];
        pe->u = to;
        pe->v = from;
        pe->c = c;
        pe->next = node[to].head;
        node[to].head = cnt;
    }

    vis[1]=true;

    int mid, ans=-1;
    while(left < right) {
        b = bb;
        mid = (left + right)/2;
        if(check(mid)) {
           right = mid; 
            ans = mid;
        } else {
            left = mid+1;
        }
    }

    if (ans == -1) {
        cout << "AFK" << endl;
    } else {
        cout << ans << endl;
    }

    return 0;
}