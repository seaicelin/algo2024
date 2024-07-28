#include <iostream>
#include <stdio.h>
using namespace std;

//namespace ice {

    const int maxn = 10005;
    const int maxe = 50005*2;
    const long long int ll_inf = 0x7fffffffffffffff;
    const int inf = 0x7fffffff;

    struct Node {
        int u;
        int f;
        int head;
        int c;
        Node() {u = f = head = c = 0;}
        bool operator<(Node& n) {
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

    struct proqueue {
        proqueue() {t=0;}
        void reset() {t=0;};
        bool ie() {return t == 0;}
        bool ne() {return t > 0;}
        void push(Node& n) {
            node[++t]=n;
            swap(t, 1);
            down(1);
        }
        void pop() {
            swap(1, t);
            t--;
            up(t);
        }
        Node top() {return node[1];}
        void swap(int a, int b) {
            Node n = node[a];
            node[a] = node[b];
            node[b] = n;
        }
        bool needMove(int child, int parent) {
            if (node[child] < node[parent]) return true;
            return false;
        }

        int lson(int pos) { return pos << 2;}
        int rson(int pos) {return (pos << 2) + 1;}
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
        Node node[maxn*1000];
    };

    Node node[maxn];
    Edge edge[maxe];
    bool vis[maxn];
    //long long int d[maxn];

    int n,m,b,bb;
    bool flag;

    proqueue q;


    void init () {
        // for (int i = 0; i < maxn; i++) {
        //     d[i]=inf;
        // }
        // d[1]=0;
    }

    bool dijkstra(int mid) {
        q.reset();

        q.push(node[1]);

        Node n;
        int u, f, v, c;
        while(q.ne()) {
            n = q.top(); q.pop();
            vis[n.u]=1;
            for (int i = n.head; i; i = edge[i].next) {
                u = edge[i].u;
                v = edge[i].v;
                c = edge[i].c;
                f = node[v].f;
                if (f < mid) continue;
                if (vis[v]) continue;
                // if (d[u] + c < d[v]) {
                //     d[v] = d[u] + c;
                //     q.push(node[v]);
                // }
            }
        }
        return false;
        //return d[n] <= b;
    }

    bool check(int mid) {
        init();
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


        int mid, ans=inf;
        while(left < right) {
            mid = (left + right)/2;
            if(check(mid)) {
            right = mid;
            if (ans > mid) ans = mid;
            } else {
                left = mid+1;
            }
        }

        if (ans == inf) {
            cout << "AFK" << endl;
        } else {
            cout << ans << endl;
        }

    }
//};

int main() {
    //ice::work();

    return 0;
}