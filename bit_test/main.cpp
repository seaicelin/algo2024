#include<stdio.h>
#include<cstdlib>
#include<ctime>

int getRand(int min, int max);
int putStep(long long state, int step, long long* p);
int getStep(long long state, int& step, long long* p);

#define SIZE 362880
#define VIS_SIZE 9
//123456780 全排列 9！

struct StateNode{
    long long state;
    int mode;
    StateNode():state(0),mode(-1) {}
};
StateNode stateList[SIZE];
int stateListLen = 0;

struct MapNode {
    long long state;
    int step;
    long long* pStart;
    MapNode():state(0),step(0), pStart(nullptr){}
};
MapNode stepMap[SIZE];





bool vis[VIS_SIZE];
void initVis() {
    for (int i = 0; i < VIS_SIZE; i++) {
        vis[i] = false;
    }
}
void getAllState(int sum, int n) {
    if (n == VIS_SIZE) {
        stateList[stateListLen++].state = sum;
        stateList[stateListLen++].mode = getRand(0, 3);
        return;
    }

    for (int i = 0; i < VIS_SIZE; i++) {
        if (vis[i]) {
            continue;
        }
        sum *=10;
        sum += i;
        vis[i] = true;
        getAllState(sum, n+1);
        sum -= i;
        sum /=10;
        vis[i] = false;
    }

}

int getRand(int min, int max) {
    return (rand() % (max - min + 1) + min);
}

int putStep(long long state, int step, long long* p) {

}

int getStep(long long state, int& step, long long* p) {
    
}

int main() {
    srand(time(0));
    getAllState(0, 0);

    printf("%lld,%d\n", stateList[0].state, stateListLen);
    printf("%lld,%d\n", stateList[stateListLen-1].state, stateListLen);

    for (int i = 0; i < 100; i++) {
        
    }

    return 0;
}