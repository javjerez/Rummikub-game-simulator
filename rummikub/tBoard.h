#ifndef tBoard_h
#define tBoard_h

#include "tSet.h"

const int MAX_SETS = NUM_TILES * 2;

typedef tSet tBoardArray[MAX_SETS];
struct tBoard {
	tBoardArray sets;
	int counter = 0;
};

void addSet(tBoard& board, tSet set);
bool play(tBoard& board, tRack& rack);
void display(tBoard board);
void displayPositions(int num);
void deleteBoard(tBoard& board);

#endif
