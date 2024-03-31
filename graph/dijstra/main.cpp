#include <iostream>
#include <stdio.h>
#include <algorithm>

using namespace std;

const int max_queue_size = 100000;
const int max_node_num = 1000;
const int INF = 0x7fffffff;

struct Node {
    int vex;
    int dis;
    Node(int v, int d): vex(v), dis(d){}
    Node():vex(-1), dis(0) {}
};
Node queue[max_queue_size];

struct Graph {
    int vex[max_node_num];
    int vex_num;
    int edge_num;
    int matrix[max_node_num][max_node_num];
};

struct Edge{
    int u;
    int v;
    int w;
};


class PriQueue {
public:
    PriQueue(Node* queue):mLen(0), mQueue(queue) {}
    void init() {mLen = 0;}
    void push(const Node& node) {
        mQueue[mLen].dis = node.dis;
        mQueue[mLen++].vex = node.vex;
        shipUp(mLen-1);
    }
    void pop() {
        if (isEmpty()) {
            return;
        }
        swap(mQueue[0], mQueue[size() - 1]);
        mLen--;
        shipDown(0);
    }
    Node* top() {
        if (isEmpty()) {
            return nullptr;
        }
        return &mQueue[0];
    }
    int size() {return mLen;}
    int lson(int i) {return 2*i + 1;}
    int rson(int i) {return 2*i + 2;}
    int parent(int i) { return (i-1)/2;}
    void shipUp(int pos) {
        int par = parent(pos);
        while(par >= 0) {
            if (mQueue[par].dis > mQueue[pos].dis) {
                swap(mQueue[par], mQueue[pos]);
                if (par == 0) {
                    break;
                }
                pos = par;
                par = parent(pos);
            } else {
                break;
            }
        }
    }
    void shipDown(int pos) {
        while(true){
            int l = lson(pos);
            int r = rson(pos);
            int min = pos;
            int curDis = mQueue[pos].dis;
            if (l < size() && mQueue[l].dis < curDis) {
                curDis = mQueue[l].dis;
                min = l;
            }
            if (r < size() && mQueue[r].dis < curDis) {
                min = r;
            }
            if (pos != min) {
                swap(mQueue[min], mQueue[pos]);
                pos = min;
            } else {
                break;
            }
        }
    }
    bool isEmpty() { return mLen == 0;}
    void swap(Node& a, Node& b) {
        Node tmp(a.vex, a.dis);
        a.dis = b.dis;
        a.vex = b.vex;
        b.dis = tmp.dis;
        b.vex = tmp.vex;
    }
private:
    int mLen;
    Node* mQueue;
};

void test_priqueue() {
    PriQueue pq(queue);
    pq.init();
    pq.push(Node(3, 5));
    pq.push(Node(4, 2));
    pq.push(Node(1, 4));

    while(!pq.isEmpty()) {
        printf("Node(%d, %d)\n", pq.top()->vex, pq.top()->dis);
        pq.pop();
    }
}

int dist[max_node_num];
int pprev[max_node_num];
bool vis[max_node_num];
int source;
Graph g;

int N; //N个节点
int M; //M条边

void initGraph() {
    for (int i = 0; i < max_node_num; i++) {
        g.vex[i] = -1;
        g.vex_num = 0;
        g.edge_num = 0;
        for (int j = 0; j < max_node_num; j++) {
            g.matrix[i][j] = INF;
        }
    }
}

void initInput() {
    cin.clear();
    initGraph();
    freopen("input.txt", "r", stdin);
    cin >> g.vex_num >> g.edge_num >> source;
    for (int i = 0; i < g.vex_num; i++) {
        g.vex[i] = i+1;
    }
    for (int i = 0; i < g.edge_num; i++) {
        //g.matrix[][];
        int u, v, w;
        cin >> u >> v >> w;
        g.matrix[u][v] = w;
    }
    fclose(stdin);
}

int main() {

    initInput();

    PriQueue qq(queue);
    qq.init();

    for (int i = 0; i < max_node_num; i++) {
        dist[i] = INF;
        vis[i] = false;
    }

    for (int i = 0; i < g.vex_num; i++) {
        int u = g.vex[i];
        pprev[u] = source;
    }

    dist[source] = 0;
    qq.push(Node(source, dist[source]));

    int u,du;
    while(!qq.isEmpty()) {
        Node node(qq.top()->vex, qq.top()->dis);
        qq.pop();

        printf("pop %d\n", node.vex);

        u = node.vex;
        du = node.dis;
        if (vis[u]) {
            continue;
        }
        
        vis[u] = true;

        for (int i = 0; i < g.vex_num; i++) {
            int v = g.vex[i];
            if(vis[v]) {
                continue;
            }
            int duv = g.matrix[u][v];
            int tmp = duv == INF? INF : du + duv;
            if (tmp < dist[v]) {
                dist[v] = tmp;
                qq.push(Node(v, tmp));
                pprev[v]=u;
            }
        }
    }

    for (int i = 0; i < g.vex_num; i++) {
        int v = g.vex[i];
        printf("u(%d)->v(%d) shortest path = %d\n",source, v, dist[v]);
        while(true) {
            if (v == source) {
                printf(" %d ", v);
                break;
            }
            printf(" %d <- ", v);
            v = pprev[v];
        }
        printf("\n");
    }

    return 0;
}