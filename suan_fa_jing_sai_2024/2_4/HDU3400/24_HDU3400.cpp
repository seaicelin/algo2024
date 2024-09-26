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

const double eps = 1e-6;

int t;
double AX,AY,BX,BY,CX,CY,DX,DY;
double P,Q,R;

double check2(double x, double y) {
    return sqrt((DX - x)*(DX - x)+(DY - y)*(DY - y))/Q;
}

double work22(double x, double y) {
    double mx,my,mx2,my2,kx,ky,c,c2;
    double lx,ly,rx,ry;
    lx = CX, ly = CY, rx = DX, ry = DY;
    do {
        kx = (rx - lx)/3;
        ky = (ry - ly)/3;
        mx = lx + kx;
        my = ly + ky;
        mx2 = rx - kx;
        my2 = ry - ky;
        c = check2(mx, my) + sqrt((mx - x)*(mx-x)+(my-y)*(my-y))/R;
        c2 = check2(mx2, my2) + sqrt((mx2 - x)*(mx2-x)+(my2-y)*(my2-y))/R;
        if (c < c2) {
            rx = mx2;
            ry = my2;
        } else {
            lx = mx;
            ly = my;
        }
    } while (abs(c-c2) > eps);
    return c;
}

double check(double x, double y) {
    return sqrt((x - AX)*(x-AX) + (y - AY) * (y - AY))/P + work22(x, y);
}

void work() {
    cin >> t;
    while(t--) {
        cin >> AX >> AY >> BX >> BY;
        cin >> CX >> CY >> DX >> DY;
        cin >> P >> Q >> R;

        double mx, my, mx2,my2,kx,ky,c,c2;
        double lx,ly,rx,ry;
        lx = AX, ly = AY, rx = BX, ry = BY;
        do {
            ky = (ry - ly)/3;
            kx = (rx - lx)/3;
            mx = lx + kx;
            my = ly + ky;
            mx2 = rx - kx;
            my2 = ry - ky;
            c = check(mx,my);
            c2 = check(mx2, my2);
            if (c < c2) {
                rx = mx2, ry = my2;
            } else {
                lx = mx, ly = my;
            }
        } while(abs(c-c2) > eps);
        log("%.2f\n", c);
    }
}

}


void solve() {
    ice::work();
}
