#include <iostream>
#include <stdio.h>
using namespace std;

#define DEBUG 1
FILE* fp;
extern void solve();

int main() {
#if DEBUG
    freopen("input.txt","r",stdin);
    setbuf(stdout, NULL);
    fp = fopen("log.txt", "w");
    setbuf(fp, NULL);
#endif

    solve();

#if DEBUG
    fclose(fp);
#endif
    return 0;
}