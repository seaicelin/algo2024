#include<stdio.h>
#include<cstdlib>
#include<ctime>

int getRand(int min, int max);
int putStep(long long state, int step, long long* p);
int getStep(long long state, int& step, long long* p);
int my_hash(long long state);

#define SIZE 362880
#define VIS_SIZE 9
#define mod 1000007
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

long long storeMode[SIZE];
int storeModeLen = 0;



bool vis[VIS_SIZE];
void initVis() {
    for (int i = 0; i < VIS_SIZE; i++) {
        vis[i] = false;
    }
}
void getAllState(int sum, int n) {
    if (n == VIS_SIZE) {
        stateList[stateListLen].state = sum;
        stateList[stateListLen].mode = getRand(0, 3);
        stateListLen++;
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

int my_hash(long long state) {
    return state % mod;
}

int putStep(long long state, int step, long long* p) {
    int key = my_hash(state);
    while(stepMap[key].step!=0) {
        if (stepMap[key].state == state) {
            return -1;
        }
        key++;
        key %= SIZE;
    }

    stepMap[key].state = state;
    stepMap[key].step = step;
    stepMap[key].pStart = p;
    return 0;
}

int getStep(long long state, int& step, long long* p) {
    int key = my_hash(state);
    while(stepMap[key].step != 0) {
        if (stepMap[key].state == state) {
            step = stepMap[key].step;
            p = stepMap[key].pStart;
            return 0;
        }
        key++;
        key %= SIZE;
    }
    return -1;
}

int main() {
    srand(time(0));
    getAllState(0, 0);

    printf("%lld,%d\n", stateList[0].state, stateListLen);
    printf("%lld,%d\n", stateList[stateListLen-1].state, stateListLen);

    //long long mode;
    //int j = 1;
    //long long state = stateList[0].state;
    //mode = stateList[0].mode;
    long long* pStart = &storeMode[storeModeLen++];
    int stepCount = 0;
    long long* pMode = pStart;
    int step = 1;
    for (int i = 0; i < 100; i++) {
        long long state = stateList[i].state;
        long long curMode = stateList[i].mode;
        //printf("curMode=%d\n", curMode);
        *pMode = (*pMode) | (curMode << (i << 1));
        step++;
        printf("i=%d,curMode=%lld,storeMode=%lld,stepCont=%d\n", i, curMode, (((*pMode) >> (i << 1)) & 0x3), stepCount);
        stepCount++;
        if (stepCount == 32) {
            stepCount = 0;
            storeModeLen++;
            pMode++;
        }
    }
    int ret = putStep(stateList[0].state, step, pStart);
    printf("putStep ret = %d\n", ret);

    ret = getStep(stateList[0].state, step, pStart);
    printf("getStep ret = %d\n", ret);
    stepCount = 0;
    for (int i = 0; i < 100; i++) {
        int mode = stateList[i].mode;
        int storeMode = (((*pStart) >> (i << 1)) & 0x3);
        if (mode != storeMode) {
            printf("fail\n");
        } else {
            printf("success\n");
        }
        stepCount++;
        if (stepCount == 32) {
            stepCount = 0;
            pStart++;
        }
    }


    return 0;
}