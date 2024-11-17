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

int t;
bool is_prim[100000000];
char s[9], s1[9], s2[9];

void init() {
    rep(i, 2, 100000000) {
        is_prim[i] = true;
        for (int j = 2; j <= i/j; j++) {
            if (i % j == 0) is_prim[i] = false;
        }
    }
}

const int dx[8]={10000000, 1000000, 100000, 10000, 1000,
                100, 10, 1};

void work() {
    init();
    cin >> t;
    int num1,num2;
    num1 = num2 = 0;
    rep(i, 1, t) {
        cin >> s;
        for (int i = 0; i <= 7; i++) {
            s1[i] = s[i] == '0'? 's':s[i];
            s2[i] = s[i] == '0'? 'e':s[i];
        }
        for (int i = 0; i <=7; i++) {
            num1 += ((s1[i]=='s'? 0: s1[i]-'0')*dx[i]);
            num2 += ((s2[i]=='s'? 0: s2[i]-'0')*dx[i]);
        }
        for (int k = num1; k <= num2; k++) {
            
        }
    }

}


}
void solve() {
    ice::work();
}