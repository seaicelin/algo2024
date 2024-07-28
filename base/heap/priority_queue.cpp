#include "main.h"

namespace ice {

    const int maxn = 100;

    struct Node {
        int v;
        Node(){v = 0;}
        Node(int v_) {v = v_;}
        bool operator < (const Node& n) const {
            return v < n.v;
        }
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
        Node q[maxn];
    };
};

void test_priority_queue() {
    
    using namespace ice;
    
    int arr[10] = {9, 4, 12, 99, 2, 3, 50, 0,0, 10};

    priority_queue q;

    for (int i = 0; i < 10; i++) {
        Node node(arr[i]);
        q.push(node);
    }
    
    while(!q.empty()) {
        cout << q.top().v << endl;
        q.pop();
    }
}


