#include<iostream>
#include<algorithm>
using namespace std;

#if 1

#define debug_sort 1 
#define debug 1
#define debug_while 1
#define debug_input 1

#endif

#define LL long long

const int maxn = 7500005;

LL a[maxn];

struct queue{
    queue(){head = tail = 0;}
    void push(int v) {q[tail++] = v;};
    LL front() {return q[head];};
    void pop_front() {head++;};
    void pop_tail() {tail--;};
    LL get(int pos) {return q[pos];}
    bool isEmpty(){return tail == head;}
    int size() {return tail - head;}
    void reset(){head = tail = 0;}
    int head;
    int tail;
    LL q[maxn];
};

queue ans, q1, q2, q3;

int quick_sort_internal(LL a[], int l, int r) {
    LL base = a[l];
    while(l < r) {
        while(l < r && a[r] <= base) r--;
        a[l]=a[r];
        while(l < r && a[l] >= base) l++;
        a[r]=a[l];
    }
    a[l]=base;
    return l;
}

void quick_sort(LL a[], int l, int r) {
    if (l >= r) return;
    int mid = quick_sort_internal(a, l, r);
    quick_sort(a, l, mid-1);
    quick_sort(a, mid+1, r);
}

LL getMaxValue() {
    LL x1,x2,x3;
    x1 = -(1 << 30);
    x2=x3=x1;
    if (!q1.isEmpty()) x1 = q1.front();
    if (!q2.isEmpty()) x2 = q2.front();
    if (!q3.isEmpty()) x3 = q3.front();
    if (x1 >= x2 && x1 >= x3) {
        q1.pop_front(); return x1;
    }
    if (x2 >= x1 && x2 >= x3) {
        q2.pop_front(); return x2;
    } 
    q3.pop_front();
    return x3;
}

void putValue(LL x, LL y) {
    if (x >= y) q2.push(x),q3.push(y);
    else q3.push(y),q2.push(x);
}

int main() {
#if debug_input
    freopen("input.txt", "r", stdin);
    setbuf(stdout, NULL);
#endif
    int n,m,q,u,v,t;
    cin >>n>>m>>q>>u>>v>>t;

    q1.reset();
    q2.reset();
    q3.reset();
    ans.reset();

    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    //std::sort(a, a+n, greater<int>());
    quick_sort(a, 0, n-1);

    for (int i = 0; i < n; i++) {
        q1.push(a[i]);
    }

#if debug_sort
    for (int i = 0; i < n; i++) {
        cout << a[i];
    }
    cout << endl;
#endif

    //float p = u/v;
    LL y = 0;

    LL b1,b2;
    for (int i = 1; i <= m; i++) {

        LL b = getMaxValue();
        b+=y, y+=q;

        ans.push(b);

        b1 = b*u/v, b2 = b - b1;

#if debug
        cout << "b="<<b << ", y = " << y << ", b1 = " <<b1 <<",b2="<< b2<<endl;
#endif 

        putValue(b1-y, b2-y);
    }

    for (int i = t; i <= m; i+=t) {
        cout << ans.get(i-1) << " ";
    }
    cout << endl;

    int tot=0;
    while(!q1.isEmpty() || !q2.isEmpty() || !q3.isEmpty()) {
        a[++tot]=getMaxValue() + y;
    }
    for (int i = t; i <= tot; i+=t) {
        cout << a[i] <<" ";
    }
    cout << endl;
#if debug_while
    while(1);
#endif
    return 0;
}