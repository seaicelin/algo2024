//#include "sec_main.h"
#include <stdio.h>

#define SIZE 3

#define test_code 0
extern void move(int mode);
/*
STATE
BFS
HASH
*/

#define STATE_SIZE (9*8*7*6*5*4*3*2*1)

static const int MOD = 10000007;
static const int MAP_NODE_SIZE = MOD + 5;
static const int rollback[4]={1, 0, 3, 2};

static int s_bfs_id = 0;

struct Node
{
    int state;
    int mode;
    Node* par;
    Node(): state(0), mode(-1), par(nullptr) {}
};

Node stateQueue[STATE_SIZE + 1];

struct MapNode {
    int state;
    int bfsId;
    MapNode():state(0),bfsId(0) {}
};

MapNode stateMap[MAP_NODE_SIZE];

static const int TARGET_PUZZLE = 123456780;

int getStateFromPuzzle(const int puzzle[SIZE][SIZE]);
void getPuzzleFromState(int state, int puzzle[SIZE][SIZE], int& start_x, int& start_y);
int my_hash(int state);
bool movePuzzle(int mode, int& start_x, int& start_y);
int putState(int state, int bfs_id);
void moveBackFromTarget(Node* node);
int findStateInCache(int state);
int putStateInCaceh(int state, int step, int index);
void moveBackFromCache(const long long& mode);

#if test_code
int test_puzzle_state_1 = 123456780;
int test_puzzle_state_2 = 12345678;
int test_puzzle_state_3 = 123405678;

int test_puzzle_1[SIZE][SIZE] = {   
    {1,2,3},
    {4,5,6},
    {7,8,0}
};
int test_puzzle_2[SIZE][SIZE] = {   
    {0,1,2},
    {3,4,5},
    {6,7,8}
};
int test_puzzle_3[SIZE][SIZE] = {   
    {1,2,3},
    {4,0,5},
    {6,7,8}
};

bool isPuzzleSame(int puzzle_1[SIZE][SIZE], int puzzle_2[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (puzzle_1[i][j] != puzzle_2[i][j]) {
                return false;
            }
        }
    }
    return true;
}

void test_puzzle_state() {
    int test_puzzle[SIZE][SIZE], x, y;
    getPuzzleFromState(test_puzzle_state_1, test_puzzle, x, y);
    if (isPuzzleSame(test_puzzle, test_puzzle_1) == false) {
        printf("test fail\n");
    }
    getPuzzleFromState(test_puzzle_state_2, test_puzzle, x, y);
    if (isPuzzleSame(test_puzzle, test_puzzle_2) == false) {
        printf("test fail\n");
    }
    getPuzzleFromState(test_puzzle_state_3, test_puzzle, x, y);
    if (isPuzzleSame(test_puzzle, test_puzzle_3) == false) {
        printf("test fail\n");
    }
    int state;
    state = getStateFromPuzzle(test_puzzle_1);
    if (state != test_puzzle_state_1) {
        printf("state != test_puzzle_state_1 fail\n");
    }
    state = getStateFromPuzzle(test_puzzle_2);
    if (state != test_puzzle_state_2) {
        printf("state != test_puzzle_state_2 fail\n");
    }
    state = getStateFromPuzzle(test_puzzle_3);
    if (state != test_puzzle_state_3) {
        printf("state != test_puzzle_state_3 fail\n");
    }
    printf("test_puzzle_state success\n");
    //while(1);
}

#endif

int getStateFromPuzzle(const int puzzle[SIZE][SIZE]) {
    int state = 0;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            state = state * 10 + puzzle[i][j];
        }
    }
    return state;
}

void getPuzzleFromState(int state, int puzzle[SIZE][SIZE], int& start_x, int& start_y) {
    for (int i = SIZE - 1; i >= 0; i--) {
        for (int j = SIZE - 1; j >= 0; j--) {
            puzzle[i][j] = state % 10;
            state /= 10;
            if (puzzle[i][j] == 0) {
                start_x = j;
                start_y = i;
            }
        }
    }
}

int my_hash(int state) {
    return state % MOD;
}

int movePuzzle(int mode, int puzzle[SIZE][SIZE], int& X, int& Y) {
    switch(mode)
    {
        case 0://from top to bottom
        if (Y != 0) {
            puzzle[Y][X] = puzzle[Y-1][X];
            Y--;
            puzzle[Y][X]=0;
            return 0;
        }
        return -1;
        case 1://from bottom to top
        if (Y != 2) {
            puzzle[Y][X] = puzzle[Y+1][X];
            Y++;
            puzzle[Y][X] = 0;
            return 0;
        }
        return -1;
        case 2://from left to right
        if (X != 0) {
            puzzle[Y][X] = puzzle[Y][X-1];
            X--;
            puzzle[Y][X] = 0;
            return 0;
        }
        return -1;
        case 3:
        if (X != 2) {
            puzzle[Y][X] = puzzle[Y][X+1];
            X++;
            puzzle[Y][X] = 0;
            return 0;
        }
        return -1;
    }
    return -1;
}

int putState(int state, int bfs_id) {
    int key = my_hash(state);
    while(stateMap[key].bfsId == bfs_id) {
        if (stateMap[key].state == state) {
            return -1;
        }
        key++;
        key %= MAP_NODE_SIZE;
    }
    stateMap[key].bfsId = bfs_id;
    stateMap[key].state = state;
    return 0;
}

struct ModeNode {
    int state;
    long long modeList;
    ModeNode():state(0),modeList(-1) {}
};

long long cacheList[STATE_SIZE];
int cacheListIndex = 0;
struct CacheNode
{
    int state;
    int step;
    int index;
    CacheNode():state(0),step(0),index(-1){}
};
CacheNode cacheMap[MAP_NODE_SIZE];

struct ModeNode {
    int state;
    int mode;
    ModeNode():state(0), mode(-1) {}
};

ModeNode modeList[500];
int modeListIndex = 0;
void moveBackFromTarget(Node* node) {
    modeListIndex = 0;
    while(node && node->mode != -1) {
        modeList[modeListIndex].mode = node->mode;
        modeList[modeListIndex++].state = node->state;
        node = node->par;
    }

    for (int i = modeListIndex - 1; i >= 0; i--) {
        move(modeList[i].mode);

        int state = modeList[i].state;
        int step = 0;
        int index = cacheListIndex;
        long long* mode = &cacheList[cacheListIndex++];
        long long tempMode = 0;
        int moveBit = 0;
        for (int j = i; j >= 0; j--) {
            tempMode = modeList[j].mode;
            (*mode) = (*mode) | (tempMode << 2*moveBit);
            printf("%d,%d");
            moveBit++;
            step++;
            if (step % 32 == 0 ) {
                mode++;
                moveBit = 0;
            }
            putStateInCaceh(state, step, index);
        }
    }

}



int findStateInCache(int state) {
    int key = my_hash(state);
    while(cacheMap[key].index != -1) {
        if (cacheMap[key].state == state) {
            return cacheMap[key].index;
        }
        key++;
        key %= MAP_NODE_SIZE;
    }
    return -1;
}

int putStateInCaceh(int state, int step, int index) {
    int key = my_hash(state);
    while(cacheMap[key].index != -1) {
        if (cacheMap[key].state == state) {
            return cacheMap[key].index;
        }
        key++;
        key %= MAP_NODE_SIZE;
    }
    cacheMap[key].index = index;
    cacheMap[key].state = state;
    cacheMap[key].state = step;
    return 0;
}

void moveBackFromCache(const long long& mode) {

}

void test(const int puzzle[SIZE][SIZE]) {
    
#if test_code
    test_puzzle_state();
#endif

    s_bfs_id++;

    int curState = getStateFromPuzzle(puzzle);

    int front, tail;
    front = tail = 0;
    
    stateQueue[tail].mode = -1;
    stateQueue[tail].state = curState;
    stateQueue[tail].par = nullptr;
    tail++;

    int cur_puzzle[SIZE][SIZE];
    int start_x, start_y;
    long long cache_mode;
    while(tail > front) {

        Node* front_node = &stateQueue[front];
        int front_state = stateQueue[front].state;
        front++;

        getPuzzleFromState(front_state, cur_puzzle, start_x, start_y);
        for (int i = 0; i < 4; i++) {

            int ret = movePuzzle(i, cur_puzzle, start_x, start_y);
            if (ret == -1) {
                continue;
            }

            int puzzle_state = getStateFromPuzzle(cur_puzzle);
            
            if (puzzle_state == TARGET_PUZZLE) {
                Node* target_node = &stateQueue[tail];
                stateQueue[tail].state = puzzle_state;
                stateQueue[tail].mode = i;
                stateQueue[tail].par = front_node;
                tail++;

                moveBackFromTarget(target_node);

                return;
            }

            ret = findStateInCache(puzzle_state);
            if (ret != -1) {
                int cacheIndex = ret;
                Node* target_node = &stateQueue[tail];
                stateQueue[tail].state = puzzle_state;
                stateQueue[tail].mode = i;
                stateQueue[tail].par = front_node;
                tail++;

                moveBackFromTarget(target_node);

                moveBackFromCache(cache_mode);
                return;
            }

            ret = putState(puzzle_state, s_bfs_id);
            if (ret == -1) {
                movePuzzle(rollback[i], cur_puzzle, start_x, start_y);
                continue;
            }

            stateQueue[tail].state = puzzle_state;
            stateQueue[tail].mode = i;
            stateQueue[tail].par = front_node;
            tail++;

            movePuzzle(rollback[i], cur_puzzle, start_x, start_y);
        }


    }
}
