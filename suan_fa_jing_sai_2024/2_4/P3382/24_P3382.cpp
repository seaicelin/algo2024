#include <stdio.h>
#include <iostream>
using namespace std;
#define DEBUG 0
#define rep(i, l, r) for(int i = (l); i <= (r); i++)
#define log(...) do{if(DEBUG) fprintf(fp, __VA_ARGS__); else printf(__VA_ARGS__);}while(0)

extern FILE* fp;

namespace P3382{

const int maxn = 15;
const double eps = 1e-8;

int n;
double l, r;
double a[maxn];

double check(double m) {
    double s = 0;
    rep(i, 1, n+1) {
        s = s*m + a[i];
    }
    return s;
}

void work() {
    cin >> n >> l >> r;
    rep(i, 1, n+1) cin >> a[i]; 
    while (abs(r - l) > eps) {
        double k = (r-l)/3.0;
        double m1 = l + k;
        double m2 = r - k;
        if (check(m1) < check(m2)) {
            l = m1;
        } else {
            r = m2;
        }  
    }
    log("%.5f\n", l);
}


}

void solve() {
    P3382::work();
}