#include <stdio.h>
#include <iostream>
using namespace std;

#define DEBUG 1

FILE* fp;
extern void solve();

int main() {
#if DEBUG
    freopen("input.txt", "r", stdin);
    setbuf(stdin, NULL);
    fp = fopen("log.txt", "w");
    setbuf(fp, NULL);
#endif

    solve();

#if DEBUG
    fclose(fp);
#endif
    return 0;
}