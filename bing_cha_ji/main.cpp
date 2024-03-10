#include "main.h"
//#include "solution.cpp"

const int SIZE = 1000;
int fa[SIZE];
int find(int i);
void uniom(int i, int j);
void init();

int find(int i) {
    if (fa[i] == i) {
        return i;
    } else {
        fa[i] = find(fa[i]);
        return fa[i];
    }
}

void uniom(int i, int j) {
    int i_fa = find(i);
    int j_fa = find(j);

    fa[i_fa] = j_fa;
}

void init() {
    for (int i = 1; i < SIZE; i++) {
        fa[i] = i;
    }

}

int main() {

    init();

    for (int i = 1; i < SIZE - 1; i++) {
        uniom(i, i + 1);
    }

    printf("1 fa = %d, 500 fa = %d, 999 fa = %d", find(1), find(500), find(999));

    return 0;
}
