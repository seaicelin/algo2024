//#include "sec_main.h"

#define SIZE 3

/*
STATE
BFS
HASH
*/

#define STATE_SIZE (9*8*7*6*5*4*3*2*1)

struct Node
{
    int state;
    int mode;
    Node(): state(0), mode(-1) {}
};

Node stateQueue[STATE_SIZE + 1];


static const int TARGET_PUZZLE = 123456780;

int getStateFromPuzzle(const int puzzle[SIZE][SIZE]);
void getPuzzleFromState(int state, int puzzle[SIZE][SIZE]);
int my_hash(int state);


int getStateFromPuzzle(const int puzzle[SIZE][SIZE]) {

}
void getPuzzleFromState(int state, int puzzle[SIZE][SIZE]) {
}

int my_hash(int state) {
}


void test(const int puzzle[SIZE][SIZE]) {
    
    int curState = getStateFromPuzzle(puzzle);

    int front, tail;
    front = tail = 0;
                        


}