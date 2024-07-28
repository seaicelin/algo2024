#include <iostream>
#include <stdio.h>
#include <queue>
using namespace std;

namespace ice {

    const int maxn = 10005;
    const int maxe = 50005*2;
    const long long int ll_inf = 0x7fffffffffffffff;
    const int inf = 0x7fffffff;

    long long d[maxn];

    struct Node {
        int u;
        int f;
        int head;
        int c;
        Node() {u = f = head = c = 0;}
        bool operator<(const Node& n) const {
            return c < n.c;
        }
    };

    struct Edge {
        int u;
        int v;
        int c;
        int next;
        Edge() {u=v=c=next=0;}
    }; 

    struct priority_queue {
        priority_queue() {t=0;}
        void reset() {t=0;};
        bool empty() {return t == 0;}
        bool ne() {return t > 0;}
        void push(Node& n) {
            q[++t]=n;
            up(t);
        }
        void pop() {
            swap(1, t);
            t--;
            down(1);
        }
        Node top() {return q[1];}
        void swap(int a, int b) {
            Node n = q[a];
            q[a] = q[b];
            q[b] = n;
        }
        bool needMove(int child, int parent) {
            if (q[child] < q[parent]) return true;
            return false;
        }

        int lson(int pos) { return pos << 1;}
        int rson(int pos) {return (pos << 1) + 1;}
        int par(int pos) {return pos >> 1;}
        void up(int pos) {
            int parent = par(pos);
            while (parent >= 1 && needMove(pos, parent)) {
                swap(pos, parent);
                pos = parent;
                parent = par(pos);
            }
        }

        void down(int pos) {
            int left, right, min;
            while(true) {
                min = pos;
                left = lson(pos);
                right = rson(pos);
                if (left <= t && needMove(left, min)) {
                    min = left;
                }
                if (right <= t && needMove(right, min)) {
                    min = right;
                }
                if (min == pos) break;
                swap(min, pos);
                pos = min;
            }
        }
        int t;
        Node q[maxe];
    };

    Node node_list[maxn];
    Edge edge[maxe];
    bool vis[maxn];

    int n,m,b,bb;
    bool flag;

    priority_queue q;

    void init () {
        for (int i = 0; i < maxn; i++) {
            d[i]=ll_inf;
            vis[i]=0;
        }
        d[1]=0;
    }

    bool dijkstra(int mid) {
        if (node_list[1].f > mid) return false;
        init();
        q.reset();
        //priority_queue<Node> q;
        q.push(node_list[1]);

        Node node;
        int u, f, v, c;
        while(!q.empty()) {
            node = q.top(); q.pop();
            if (vis[node.u]) continue;
            vis[node.u]=1;
            for (int i = node.head; i; i = edge[i].next) {
                u = edge[i].u;
                v = edge[i].v;
                c = edge[i].c;
                f = node_list[v].f;
                if (f > mid) continue;
                if (vis[v]) continue;
                if (d[u] + c < d[v]) {
                    d[v] = d[u] + c;
                    node = node_list[v];
                    node.c = c;
                    q.push(node);
                }
            }
        }
        return d[n] <= b;
    }

    bool check(int mid) {
        return dijkstra(mid);
    }

    void work() {
        freopen("input.txt","r",stdin);
        setbuf(stdout, NULL);

        int left,right;
        left = inf;
        right = 0;

        cin>>n>>m>>b;

        int f;
        for (int i = 1; i <= n; i++) {
            cin >> f;
            node_list[i].u = i;
            node_list[i].f = f;
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
            pe->next = node_list[from].head;
            node_list[from].head = cnt;
        
            pe = &edge[++cnt];
            pe->u = to;
            pe->v = from;
            pe->c = c;
            pe->next = node_list[to].head;
            node_list[to].head = cnt;
        }

        if (!dijkstra(inf)) {
            cout << "AFK" << endl;
            return;
        }

        int mid, ans=inf;
        while(left < right) {
            mid = (left + right)/2;
            if(check(mid)) {
                right = mid;
                ans = mid;
            } else {
                left = mid+1;
            }
        }
        cout << ans << endl;
    }
};

int main() {
    ice::work();
    return 0;
}